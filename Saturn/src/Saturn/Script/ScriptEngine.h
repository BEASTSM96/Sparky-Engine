#pragma once

#include "Saturn/Core/Base.h"
#include "Saturn/Scene/Entity.h"
#include <string>

#include <mono/metadata/assembly.h>
#include <mono/metadata/debug-helpers.h>
#include <mono/metadata/object.h>

extern "C" {
	typedef struct _MonoObject MonoObject;
	typedef struct _MonoClassField MonoClassField;
};

namespace Saturn {

	enum class FieldType
	{
		None = 0,
		Float,
		Int,
		UnsignedInt,
		String,
		Vec2,
		Vec3,
		Vec4
	};

	static FieldType MonoToSaturn( MonoType* monoType )
	{
		int type = mono_type_get_type( monoType );
		switch( type )
		{
			case MONO_TYPE_R4: return FieldType::Float;
			case MONO_TYPE_I4: return FieldType::Int;
			case MONO_TYPE_U4: return FieldType::UnsignedInt;
			case MONO_TYPE_STRING: return FieldType::String;
			case MONO_TYPE_VALUETYPE: 
			{
				char* name = mono_type_get_name( monoType );
				if( strcmp( name, "Saturn.Vector2" ) == 0 ) return FieldType::Vec2;
				if( strcmp( name, "Saturn.Vector3" ) == 0 ) return FieldType::Vec3;
				if( strcmp( name, "Saturn.Vector4" ) == 0 ) return FieldType::Vec4;
			}
			default:
				return FieldType::None;
				break;
		}
	}

	struct MonoUtils
	{
	public:
		static MonoMethod* GetMethod( MonoImage* image, const std::string& desc );
		static MonoObject* CallMethod( MonoObject* obj, MonoMethod* method, void** parms = nullptr );

		static void PrintClassMethod( MonoClass* monoClass );
		static void PrintClassProps( MonoClass* monoClass );
	};

	struct EntityClass 
	{
		std::string FullName;
		std::string ClassName;
		std::string NamespaceName;
		
		MonoClass* Class;
		MonoMethod* MethodOnCreate;
		MonoMethod* MethodBeginPlay;
		MonoMethod* MethodOnUpdate;
		MonoMethod* MethodOnDestory;
		MonoMethod* MethodOnCollisionEnter;
		MonoMethod* MethodOnCollisionExit;
		MonoMethod* MethodOnCollisionStay;
		MonoMethod* MethodOnTriggerEnter;
		MonoMethod* MethodOnTriggerExit;

		void InitClassMethods( MonoImage* image )
		{
			MethodOnCreate   =  MonoUtils::GetMethod( image, FullName + ":OnCreate()" );
			MethodBeginPlay  =  MonoUtils::GetMethod( image, FullName + ":OnBeginPlay()" );
			MethodOnUpdate   =  MonoUtils::GetMethod( image, FullName + ":OnUpdate(single)" );
			MethodOnDestory  =  MonoUtils::GetMethod( image, FullName + ":OnDestory()" );
		}

	};

	struct EntityInstance
	{
		EntityClass* ScrtptClass;

		uint32_t Handle;
		Scene* SceneInstance;

		MonoObject* Get() 
		{
			return mono_gchandle_get_target( Handle );
		}
	};

	struct PublicField
	{
		std::string Name;
		FieldType Type;

		PublicField(const std::string& name, FieldType type) 
			: Name(name), Type(type) {}

		template<typename Ty>
		Ty GetValue() const 
		{
			Ty value;
			GetValue_Internal( &value );
			return value;
		}

		template<typename Ty>
		void SetValue( Ty value ) const
		{
			SetValue_Internal( &value );
		}

	private:
		EntityInstance* m_EntityInstance;
		MonoClassField* m_MonoClassField;

		void GetValue_Internal( void* value );
		void SetValue_Internal( void* outValue );


		friend class ScriptEngine;
	};

	using FieldMap = std::unordered_map<std::string, std::vector<PublicField>>;

	class ScriptEngine
	{
	public:
		ScriptEngine();
		~ScriptEngine();

		static void Init( const std::string& path );
		static void Shutdown();

		static void OnCreateEntity( Entity entity );
		static void OnEntityBeingPlay( uint32_t entityID );
		static void OnUpdateEntity( uint32_t entityID, Timestep ts );
		static void OnInitEntity( Entity entity );

		static const FieldMap& GetFieldMap();

	private:

	};
}