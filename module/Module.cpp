#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>

#include <ini.h>

#include <SDKHelper.h>

using namespace std;

// The modules internal name (Also used for the namespace name)
MODULE_MAIN("ini");

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
			case SI_OK: {
				SDK::StringValue Value("ok", 2);
				State.Return(Value);
			}
			break;
			case SI_UPDATED: {
				SDK::StringValue Value("updated", 7);
				State.Return(Value);			
			}
			break;
			case SI_INSERTED: {
				SDK::StringValue Value("inserted", 8);
				State.Return(Value);						
			}
			break;
			case SI_FAIL: {
				SDK::StringValue Value("fail", 4);
				State.Return(Value);				
			}
			break;
			case SI_NOMEM: {
				SDK::StringValue Value("nomem", 5);
				State.Return(Value);	
			}
			break;
			case SI_FILE: {
				SDK::StringValue Value("file", 4);
				State.Return(Value);	
			}
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
			return pState->SetError("[INI] Can't delete INI entry (missing pointer)");
		}

		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);		
		bool bRemoveEmpty;
		State.CheckBoolean(2, bRemoveEmpty);

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

		CSimpleIni *ini = (CSimpleIni*)pThis;
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

		CSimpleIni *ini = (CSimpleIni*)pThis;
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

		CSimpleIni *ini = (CSimpleIni*)pThis;
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

		CSimpleIni *ini = (CSimpleIni*)pThis;
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

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't get INI using spaces state (missing pointer)");
		}

		bool result = ini->UsingSpaces();
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

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't set INI unicode state (missing pointer)");
		}

		bool bUnicode;
		State.CheckBoolean(0, bUnicode);
		
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

		CSimpleIni *ini = (CSimpleIni*)pThis;
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

		CSimpleIni *ini = (CSimpleIni*)pThis;
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

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		bool bDefaultValue = false;
		State.CheckBoolean(2, bDefaultValue);
		
		bool bResult = ini->GetDoubleValue(szSection, szKey, bDefaultValue);

		SDK::BooleanValue Value(bResult);
		State.Return(Value);

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

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		int iDefaultValue = 0;
		State.CheckNumber(2, iDefaultValue);
		
		int iResult = ini->GetDoubleValue(szSection, szKey, iDefaultValue);

		SDK::NumberValue Value(iResult);
		State.Return(Value);

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

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't load INI file (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		double fDefaultValue = 0;
		State.CheckNumber(2, fDefaultValue);
		
		double fResult = ini->GetDoubleValue(szSection, szKey, fDefaultValue);

		SDK::NumberValue Value(fResult);
		State.Return(Value);

		return true;

		SDK_ENDTRY;
	});
	
	g_pINIFileClass.RegisterFunction("getStringValue", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't get string value (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't get string value (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		const char *szDefaultValue = State.CheckString(2);
		
		const char *szResult = ini->GetValue(szSection, szKey, szDefaultValue);

		SDK::StringValue Value(szResult);
		State.Return(Value);

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

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't set boolean value (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		bool bValue = false;
		State.CheckBoolean(2, bValue);
		
		char szComment[128];
		bool hasComment = false;
		if (State.CheckString(3)) {
			strcpy(szComment, ";");
			strcat(szComment, State.CheckString(3));

			hasComment = true;
		}
		
		bool bForceReplace = false;
		State.CheckBoolean(4, bForceReplace);
		
		SI_Error result;
		if (hasComment) {
			result = ini->SetBoolValue(szSection, szKey, bValue, szComment, bForceReplace);
		} else {
			result = ini->SetBoolValue(szSection, szKey, bValue, 0, bForceReplace);
		}

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

	g_pINIFileClass.RegisterFunction("setIntValue", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't set integer value (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't set integer value (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		int iValue = 0;
		State.CheckNumber(2, iValue);
		
		char szComment[128];
		bool hasComment = false;
		if (State.CheckString(3)) {
			strcpy(szComment, ";");
			strcat(szComment, State.CheckString(3));

			hasComment = true;
		}
		
		bool bUseHex = false;
		State.CheckBoolean(4, bUseHex);		
		
		bool bForceReplace = false;
		State.CheckBoolean(5, bForceReplace);
		
		SI_Error result;
		if (hasComment) result = ini->SetLongValue(szSection, szKey, iValue, szComment, bUseHex, bForceReplace);
		else result = ini->SetLongValue(szSection, szKey, iValue, 0, bForceReplace);

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

	g_pINIFileClass.RegisterFunction("setFloatValue", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't set float value (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't set float value (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		double fValue = 0;
		State.CheckNumber(2, fValue);
		
		char szComment[128];
		bool hasComment = false;
		if (State.CheckString(3)) {
			strcpy(szComment, ";");
			strcat(szComment, State.CheckString(3));

			hasComment = true;
		}
		
		bool bForceReplace = false;
		State.CheckBoolean(4, bForceReplace);
		
		SI_Error result;
		if (hasComment) result = ini->SetDoubleValue(szSection, szKey, fValue, szComment, bForceReplace);
		else result = ini->SetDoubleValue(szSection, szKey, fValue, 0, bForceReplace);

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

	g_pINIFileClass.RegisterFunction("setStringValue", [](Galactic3D::Interfaces::INativeState* pState, int32_t argc, void* pUser) {
		SDK_TRY;

		SDK::State State(pState);
		
		auto pThis = State.CheckThis<CSimpleIni, g_pINIFileClass>();		
		
		if (!pThis) {
			return pState->SetError("[INI] Can't set string value (missing pointer)");
		}

		CSimpleIni *ini = (CSimpleIni*)pThis;
		if (!ini) {
			return pState->SetError("[INI] Can't set string value (missing pointer)");
		}
		
		const char *szSection = State.CheckString(0);
		const char *szKey = State.CheckString(1);
		const char *szValue = State.CheckString(2);
		
		char szComment[128];
		bool hasComment = false;
		if (State.CheckString(3)) {
			strcpy(szComment, ";");
			strcat(szComment, State.CheckString(3));

			hasComment = true;
		}
		
		bool bForceReplace = false;
		State.CheckBoolean(4, bForceReplace);
		
		SI_Error result;
		if (hasComment) result = ini->SetValue(szSection, szKey, szValue, szComment, bForceReplace);
		else result = ini->SetValue(szSection, szKey, szValue, 0, bForceReplace);

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
}

void ModuleUnregister()
{
}
