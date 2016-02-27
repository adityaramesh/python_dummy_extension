#include <array>
#include <cstring>
#include <algorithm>
#include <experimental/string_view>

#include <Python.h>

#define EXPORT_SYMBOL __attribute__((visibility("default")))

namespace {

using obj_ptr = PyObject*;
using std::experimental::basic_string_view;
using string_view = basic_string_view<uint8_t>;

auto make_string_view(const obj_ptr str)
{
	auto kind       = PyUnicode_KIND(str);
	auto codepoints = PyUnicode_GET_LENGTH(str);
	auto len        = Py_ssize_t{};

	switch (kind) {
	case PyUnicode_WCHAR_KIND: len = sizeof(wchar_t) * codepoints; break;
	case PyUnicode_1BYTE_KIND: len = codepoints;                   break;
	case PyUnicode_2BYTE_KIND: len = 2 * codepoints;               break;
	case PyUnicode_4BYTE_KIND: len = 4 * codepoints;               break;
	default: throw std::runtime_error{"Invalid constant for unicode kind."};
	}

	using string_view = basic_string_view<uint8_t>;
	return string_view{(uint8_t*)PyUnicode_DATA(str), size_t(len)};
}

extern "C"
auto make_message(obj_ptr, obj_ptr) noexcept
{ return PyUnicode_FromString("Hello, world!"); }

extern "C"
auto reverse(obj_ptr, obj_ptr args) noexcept
{
	auto src_obj = obj_ptr{};

	if (not PyArg_ParseTuple(args, "O", &src_obj))
		return obj_ptr{};

	try {
		auto src = make_string_view(src_obj);
		auto dst_obj = PyUnicode_New(src.size(), PyUnicode_MAX_CHAR_VALUE(src_obj));
		if (not dst_obj)
			return obj_ptr{};

		std::reverse_copy(src.begin(), src.end(), PyUnicode_1BYTE_DATA(dst_obj));
		return dst_obj;
	}
	catch (const std::runtime_error& e) {
		PyErr_SetString(PyExc_RuntimeError, e.what());
		return obj_ptr{};
	}
}

auto method_def = std::array<PyMethodDef, 3>{{
	{"make_message", make_message, METH_NOARGS,  "Returns a message in the form of a string."},
	{"reverse",      reverse,      METH_VARARGS, "Returns a new string that is the reverse of "
		"the given string. For simplicity, we assume that each visible character is one "
		"code point."},
	{nullptr, nullptr, 0, nullptr}
}};

auto module_def = PyModuleDef{
	PyModuleDef_HEAD_INIT,
	 // Module name.
	"_dummy",
	// Module docstring.
	"An example Python extension module written in C++.",
	// Size of per-interpreter state of the module, or -1 if the module keeps its state
	// in global variables.
	-1,
	method_def.data()
};

extern "C" EXPORT_SYMBOL
auto PyInit__dummy() noexcept
{ return PyModule_Create(&module_def); }

}
