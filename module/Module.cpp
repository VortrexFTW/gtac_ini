#include "StdInc.h"

#include <stdio.h>

#include <SDHHelper.h>
#include <ini.h>

// The modules internal name (Also used for the namespace name)
MODULE_MAIN("mysql");

SDK::Class g_pINIFileClass;

void ModuleRegister()
{
	g_pINIFileClass = SDK::Class("INI");

	SDK::RegisterFunction("create", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		CSimpleIni *ini = new CSimpleIni();

		SDK::ClassValue<CSimpleIni, g_pINIFileClass> Value(new CSimpleIni(ini));
		State.Return(Value);
		
		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("close", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't close INI file (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't close INI file (missing pointer)");
		}

		delete ini;

		ini = NULL;

		SDK::BooleanValue Value(true);
		State.Return(Value);

		return true;

		SDK_ENDTRY;		
	});

	g_pINIFileClass.RegisterFunction("errno", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		int err;
		State.CheckNumber(0, err);

		switch (err) {
			case SI_OK:
				SDK::StringValue Value("ok", 2);
				State.Return(Value);
				break;
			case SI_UPDATED:
				SDK::StringValue Value("updated", 7);
				State.Return(Value);			
				break;
			case SI_INSERTED:
				SDK::StringValue Value("inserted", 8);
				State.Return(Value);						
				break;
			case SI_FAIL:
				SDK::StringValue Value("fail", 4);
				State.Return(Value);				
				break;
			case SI_NOMEM:
				SDK::StringValue Value("nomem", 5);
				State.Return(Value);	
				break;
			case SI_FILE:
				SDK::StringValue Value("file", 4);
				State.Return(Value);	
				break;
		}

		return true;
		
		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("reset", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't reset INI (missing pointer)");
		}

		const char *szDefaultValue = State.CheckString(0);
		if (!szDefaultValue) szDefaultValue = "";

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't reset INI (missing pointer)");
		}

		ini->Reset();

		SDK::BooleanValue Value(true);
		State.Return(Value);

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("delete", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't reset INI (missing pointer)");
		}

		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);		
		bool *bRemoveEmpty = State.CheckBoolean(2);

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't delete INI entry (missing pointer)");
		}

		bool result = ini->Delete(szSection, szKey, bRemoveEmpty);
		if (result) {
			SDK::BooleanValue Value(true);
			State.Return(Value);
		} else {
			SDK::BooleanValue Value(false);
			State.Return(Value);
		}

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.AddProperty("isEmpty", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't get INI empty state (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't get INI empty state (missing pointer)");
		}

		bool result = ini->IsEmpty();
		if (result) {
			SDK::BooleanValue Value(true);
			State.Return(Value);
		} else {
			SDK::BooleanValue Value(false);
			State.Return(Value);
		}

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.AddProperty("isMultiKey", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't get INI multi-key state (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't get INI multi-key state (missing pointer)");
		}

		bool result = ini->IsMultiKey();
		if (result) {
			SDK::BooleanValue Value(true);
			State.Return(Value);
		} else {
			SDK::BooleanValue Value(false);
			State.Return(Value);
		}

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.AddProperty("isMultiLine", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't get INI multi-line state (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't get INI multi-line state (missing pointer)");
		}

		bool result = ini->IsMultiLine();
		if (result) {
			SDK::BooleanValue Value(true);
			State.Return(Value);
		} else {
			SDK::BooleanValue Value(false);
			State.Return(Value);
		}

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.AddProperty("isUnicode", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't get INI unicode state (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't get INI unicode state (missing pointer)");
		}

		bool result = ini->IsUnicode();
		if (result) {
			SDK::BooleanValue Value(true);
			State.Return(Value);
		} else {
			SDK::BooleanValue Value(false);
			State.Return(Value);
		}

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.AddProperty("isUsingSpaces", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't get INI using-spaces state (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't get INI using spaces state (missing pointer)");
		}

		bool result = ini->IsUsingSpaces();
		if (result) {
			SDK::BooleanValue Value(true);
			State.Return(Value);
		} else {
			SDK::BooleanValue Value(false);
			State.Return(Value);
		}

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("setUnicode", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't set INI unicode state (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't set INI unicode state (missing pointer)");
		}

		bool *bUnicode = State.CheckBoolean(0);
		
		ini->SetUnicode(bUnicode);

		SDK::BooleanValue Value(true);
		State.Return(Value);

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("loadFile", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}
		
		const char *szFilename = State.CheckString(0);

		SI_Error result = ini->LoadFile(szFilename);
		
		SDK::NumberValue Value(result);
		State.Return(Value);

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("saveFile", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}
		
		const char *szFilename = State.CheckString(0);

		if (ini->SaveFile(szFilename, true) < 0) {
			return pState->SetError("[INI] Can't save INI file %s", szFilename);
		}

		if (ini) delete ini;
		ini = NULL;

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("getBoolValue", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		bool bDefaultValue = false;
		
		if(!State.CheckBoolean(2)) {
			bDefaultValue = false;
		}
		
		bool bResult = ini->GetDoubleValue(szSection, szKey, bDefaultValue);

		SDK::BooleanValue Value(bResult);
		State.Return(bResult);

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("getIntValue", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		int iDefaultValue = 0;
		
		if(State.CheckNumber(2)) {
			iDefaultValue = State.CheckNumber(2, iDefaultValue);
		}
		
		int iResult = ini->GetDoubleValue(szSection, szKey, iDefaultValue);

		SDK::NumberValue Value(iResult);
		State.Return(iResult);

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("getFloatValue", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		double fDefaultValue = 0;
		
		if(State.CheckNumber(2)) {
			fDefaultValue = State.CheckNumber(2, fDefaultValue);
		}
		
		double fResult = ini->GetDoubleValue(szSection, szKey, fDefaultValue);

		SDK::NumberValue Value(fResult);
		State.Return(fResult);

		return true;

		SDK_ENDTRY;
	});

	g_pINIFileClass.RegisterFunction("setBoolValue", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't set boolean value (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't set boolean value (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		bool bValue = false;
		if (!State.CheckBoolean(2, bValue)) {
			return pState->SetError("[INI] Can't set boolean value (missing value)");
		}
		
		char szComment[128];
		bool hasComment = false;
		if (State.CheckString(3)) {
			strcpy_s(szComment, ";");
			strcat(szComment, State.CheckString(3));

			hasComment = true;
		}
		
		bool bForceReplace = false;
		if (!State.CheckBoolean(4, bForceReplace)) {
			bForceReplace = false;		
		}
		
		SI_Error result;
		if (hasComment) result = ini->SetBoolValue(szSection, szKey, bValue, szComment, bForceReplace);
		else result = ini->SetBoolValue(szSection, szKey, bValue, 0, bForceReplace);

		if (result == SI_OK) {
			SDK::BooleanValue Value(true);
			State.Return(Value);
		} else {
			SDK::BooleanValue Value(false);
			State.Return(Value);			
		}

		return true;

		SDK_ENDTRY;
	});

	Galactic_ReflectedClass_RegisterFunction(g_pINIFileClass, "setIntValue", "", [](GNativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't set integer value (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pState;
		if (!ini) {
			return pState->SetError("[INI] Can't set integer value (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		int iValue = 0;
		if (!State.CheckNumber(2, iValue)) {
			return pState->SetError("[INI] Can't set integer value (missing value)");
		}
		
		char szComment[128];
		bool hasComment = false;
		if (State.CheckString(3)) {
			strcpy_s(szComment, ";");
			strcat(szComment, State.CheckString(3));

			hasComment = true;
		}
		
		bool bForceReplace = false;
		if (!State.CheckBoolean(4, bForceReplace)) {
			bForceReplace = false;		
		}
		
		SI_Error result;
		if (hasComment) result = ini->SetBoolValue(szSection, szKey, iValue, szComment, bForceReplace);
		else result = ini->SetBoolValue(szSection, szKey, iValue, 0, bForceReplace);

		if (result == SI_OK) {
			SDK::BooleanValue Value(true);
			State.Return(Value);
		} else {
			SDK::BooleanValue Value(false);
			State.Return(Value);			
		}

		return true;

		SDK_ENDTRY;
	});

	Galactic_ReflectedClass_RegisterFunction(g_pINIFileClass, "setFloatValue", "", [](GNativeState* pState, int32_t argc, void* pUser) {
		GRefCounted *pINIRef = Galactic_NativeState_GetThis(pState, g_pINIFileClass);
		if (!pINIRef) {
			return Galactic_NativeState_SetError(pState, "ini.setFloatValue: missing pointer\n");
		}

		const char *szSection = Galactic_NativeState_CheckString(pState, 0);
		if (!szSection) {
			return Galactic_NativeState_SetError(pState, "ini.setFloatValue: empty sector name\n");
		}

		const char *szKey = Galactic_NativeState_CheckString(pState, 1);
		if (!szKey) {
			return Galactic_NativeState_SetError(pState, "ini.setFloatValue: empty key name\n");
		}

		double nValue = 0.0;
		if (!Galactic_NativeState_CheckDouble(pState, 2, nValue)) {
			return Galactic_NativeState_SetError(pState, "ini.setFloatValue: empty float value\n");
		}

		char szComment[128];
		bool hasComment = false;
		if (Galactic_NativeState_CheckString(pState, 3)) {
			strcpy_s(szComment, ";");
			strcat(szComment, Galactic_NativeState_CheckString(pState, 3));

			hasComment = true;
		}

		bool bForceReplace = false;
		if (!Galactic_NativeState_CheckBoolean(pState, 4, bForceReplace)) bForceReplace = false;

		CSimpleIni *ini = (CSimpleIni*)Galactic_Referenceable_GetPrivate(pINIRef);
		if (!ini) {
			return Galactic_NativeState_SetError(pState, "ini.setFloatValue: missing pointer\n");
		}

		SI_Error result;
		if (hasComment) result = ini->SetDoubleValue(szSection, szKey, nValue, szComment, bForceReplace);
		else result = ini->SetDoubleValue(szSection, szKey, nValue, 0, bForceReplace);

		if (result == SI_OK) Galactic_NativeState_ReturnBoolean(pState, true);
		else Galactic_NativeState_ReturnBoolean(pState, false);

		return true;
	});

	Galactic_ReflectedClass_RegisterFunction(g_pINIFileClass, "setString", "", [](GNativeState* pState, int32_t argc, void* pUser) {
		GRefCounted *pINIRef = Galactic_NativeState_GetThis(pState, g_pINIFileClass);
		if (!pINIRef) {
			return Galactic_NativeState_SetError(pState, "ini.setString: missing pointer\n");
		}

		const char *szSection = Galactic_NativeState_CheckString(pState, 0);
		if (!szSection) {
			return Galactic_NativeState_SetError(pState, "ini.setString: empty sector name\n");
		}

		const char *szKey = Galactic_NativeState_CheckString(pState, 1);
		if (!szKey) {
			return Galactic_NativeState_SetError(pState, "ini.setString: empty key name\n");
		}

		const char *szValue = Galactic_NativeState_CheckString(pState, 2);
		if (!szValue) {
			return Galactic_NativeState_SetError(pState, "ini.setString: empty string value\n");
		}

		char szComment[128];
		bool hasComment = false;
		if (Galactic_NativeState_CheckString(pState, 3)) {
			strcpy_s(szComment, ";");
			strcat(szComment, Galactic_NativeState_CheckString(pState, 3));

			hasComment = true;
		}

		bool bForceReplace = false;
		if (!Galactic_NativeState_CheckBoolean(pState, 4, bForceReplace)) bForceReplace = false;

		CSimpleIni *ini = (CSimpleIni*)Galactic_Referenceable_GetPrivate(pINIRef);
		if (!ini) {
			return Galactic_NativeState_SetError(pState, "ini.setString: missing pointer\n");
		}

		SI_Error result;
		if (hasComment) result = ini->SetValue(szSection, szKey, szValue, szComment, bForceReplace);
		else result = ini->SetValue(szSection, szKey, szValue, 0, bForceReplace);

		if (result == SI_OK) Galactic_NativeState_ReturnBoolean(pState, true);
		else Galactic_NativeState_ReturnBoolean(pState, false);

		return true;
	});

	printf("[INI] Module loaded \n");
	printf("[INI] Build date: %s \n", __DATE__);

	return nullptr;
}

extern "C" __declspec(dllexport) void _cdecl UnregisterModule(void* pUser)
{
}