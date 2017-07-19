#pragma once

// Macros for simple service locator creation.
// Reason for not using templates: 
// static members + templates is not a good combination if
// we want to use dynamically linked libraries in the future.

// Put at end of header file for whatever type you want access to
#define SERVICE_LOCATOR_HEADER(TYPE, NAME)					\
class NAME													\
{															\
public:														\
	static TYPE* get();										\
	static void provide(TYPE* service);						\
private:													\
	static TYPE* service_;									\
};

// Put at end of source file
#define SERVICE_LOCATOR_SOURCE(TYPE, NAME)					\
TYPE* NAME::service_ = nullptr;								\
void NAME::provide(TYPE* service) { service_ = service; }	\
TYPE* NAME::get() { return service_; }
