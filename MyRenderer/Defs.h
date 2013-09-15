#pragma once

#define MAKE_STATIC(class_name) \
	private: \
	class_name () {} \
	class_name ( const class_name & other ) {} \
	class_name operator = ( const class_name & other ) { return *this; }