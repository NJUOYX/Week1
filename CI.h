#pragma once
#include"pch.h"

constexpr auto TOP_CI_FILE_PATH = "G:\\Ñ§µÜ\\Week1Pro_public\\TOP_CI.txt";
constexpr auto ROOT_CI_FILE_PATH = "G:\\Ñ§µÜ\\Week1Pro_public\\ROOT_CI.txt";
constexpr auto STOP_TRAP = "user stop";

class CI {
public:
	static WString format_wstr_vector(WStr_Vec vec);
};

class Account_CI {
public:
	struct Account_Info
	{
		String id;
		String password;
	};
	enum class BaseCall
	{
		ROOT_LOGIN_REQUIRE=1,
		STUDENT_LOGIN_REQUIRE,
		STUDENT_REGIST_REQUIRE,
		STOP,
		CONTINUE
	};
	enum class BaseResponse
	{
		ROOT_LOGIN_FAIL,
		ROOT_LOGIN_SUCCESS,
		STUDENT_LOGIN_FAIL,
		STUDENT_LOGIN_SUCCESS,
		STUDENT_REGIST_FAIL,
		STUDENT_REGIST_SUCCESS
	};
public:
	Account_CI() = default;
	BaseCall top_show(Account_Info&info);
	BaseCall responseshow(BaseResponse response, Account_Info&info);
private:

private:
	const String TOP_CI_filepath = TOP_CI_FILE_PATH;
	const String ROOT_LOGIN_ID_REQUIRE;
	const String ROOT_LOGIN_PASSWORD_REQUIRE;
	const String STUDENT_LOGIN_ID_REQUIRE;
	const String STUDENT_LOGIN_PASSWORD_REQUIRE;
	const String ROOT_LOGIN_SUCCESS;
	const String ROOT_LOGIN_FAIL;
	const String STUDENT_LOGIN_SUCCESS;
	const String STUDENT_LOGIN_FAIL;
	const String STUDENT_REGITST_SUCCESS;
	const String STUDENT_REGIST_FAIL;
	const String STUDENT_REGIST_ID_REQUIRE;
	const String STUDENT_REGIST_PASSWORD_REQUIRE;
	const String WAITING_TO_CONTINUE;
	const String STOP;
};

class Root_CI {
public:
	enum class Root_Function
	{
		LOG_OUT=1,
		FILE_INFO_IN,
		LIST_ALL_COURSES,
		ADD_COURSES,
		DEL_COURSES,
		MODIFY_COURSES,
		CHECK_COURSES
	};
	enum class BaseResponse
	{
		FILE_INFO_IN_FAIL,
		FILE_INFO_IN_SUCCESS,
		LIST_ALL_COURSES_SUCCESS,
		LIST_ALL_COURSES_FAIL,
		ADD_COURSES_SUCCESS,
		ADD_COURSES_FAIL,
		DEL_COURSES_SUCCESS,
		DEL_COURSES_FAIL,
		MODIFY_COURSES_SUCCESS,
		MODIFY_COURSES_FAIL,
		CHECK_COURSES_SUCCESS,
		CHECK_COURSES_FAIL
	};
public:
	Root_CI() = default;
	Root_Function exc(String&info);
	Root_Function baseresponse(BaseResponse response, String const& info);
	WStr_Vec get_in(WStr_Vec signals);
	String get_base_file_path()const;
private:
	String Root_CI_File_path = ROOT_CI_FILE_PATH;
};

class Student_CI {
public:
	enum class Student_Function
	{
		LOG_OUT,
		LIST_ALL_COURSES,
		CHOOSE_COURSE,
		CHECK_MY_COURSES,
		GIVE_UP_MY_COURSE,
		TO_BE_ASSISTANT,
		CHOOSE_MY_ASSISTANT
	};
	enum class BaseResponse{
		LIST_ALL_COURSES_SUCCESS,
		LIST_ALL_COURSES_FAIL,
		CHOOSE_COURSE_SUCCESS,
		CHOOSE_COURSE_FAIL,
		CHECK_MY_COURSES_SUCCESS,
		CHECK_MY_COURSES_FAIL,
		GIVE_UP_MY_COURSES_SUCCESS,
		GIVE_UP_MY_COURSES_FAIL,
		TO_BE_ASSISTANT_SUCCESS,
		TO_BE_ASSISTANT_FAIL,
		CHOOSE_MY_ASSISTANT_SUCCESS,
		CHOOSE_MY_ASSISTANT_FAIL
	};
public:
	Student_CI() = default;
	Student_Function exc(String& info);
	Student_Function baseresponse(BaseResponse response, String const& info);
};