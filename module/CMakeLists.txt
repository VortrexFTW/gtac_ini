disable_rtti()

file(GLOB_RECURSE SOURCES *.cpp *.h)

if(MSVC)
	precompiled_header(pch)
endif()

new_library_shared(mod_ini "${SOURCES}" "")
set_target_properties(mod_ini PROPERTIES FOLDER modules)
