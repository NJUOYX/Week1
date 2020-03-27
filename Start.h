#pragma once
#include"CourseBase.h"
#include"CI.h"
class Start {
public:
	Start();
	int exc();
private:
	int login();
	int Root_Operation();
	int Stu_Operation();
private:
	Course read_course_from_strs(WStr_Vec strs);
	int32_t read_int32_from_strs(WStr_Vec strs);
private:
	CourseBase* base;
	Root_Account* current_user;
private:
	const String Base_not_init;
	const String Base_had_init;
	const String Teacher_modify_success;
	const String Teacher_modify_fail;
	const String max_students_modify_success;
	const String max_students_modify_fail;
};