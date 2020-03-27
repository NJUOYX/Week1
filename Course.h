#pragma once
#include"Account.h"
constexpr auto ASSITANT_MAX_COUESE = 2;
constexpr auto DEFAULT_INFO_LINE = 5;
class Assistant :public Student_Account {
public:
	Assistant();
	Assistant(String student_id, String student_password);
	bool choice_full()const;
	int32_t get_current_coursesChoices()const;
	bool operator ==(Assistant const& assi)const;
	bool operator <(Assistant const& assi)const;
	Assistant const& operator =(Assistant const& assi);
	bool addchoice();
	bool dechoice();
	int32_t get_max_coursesChoices()const;
	String get_sid()const;
private:
	const int32_t max_coursesChoices;
	int32_t current_coursesChoices;
};

class Student :public Assistant{
public:
	Student() = default;
	Student(String student_id, String student_password);
	Assistant my_assistant()const;
	bool set_myAssistant(Assistant const&assi);
	bool is_setAssistant()const;

private:
	void set_I_haveAssistant();
private:
	Assistant myAssistant;
	bool is_set_Assistant;
};


struct Course_default_Info
{
	Course_default_Info() = default;
	Course_default_Info(int32_t course_id, WString course_name, WString course_teacher, 
		int32_t max_students, WString course_type);
	Course_default_Info(WString course_name, WString course_teacher,
		int32_t max_students, WString course_type);
	int32_t course_id;
	WString course_name;
	WString course_teacher;
	int32_t max_students;
	WString course_type;
};
constexpr auto COURSE_ID = "课程ID";
constexpr auto COURSE_NAME = "课程名称";
constexpr auto COURSE_TEACHER = "课程教师";
constexpr auto MAX_STUDENTS = "最大学生数";
constexpr auto COURSE_TYPE = "课程类型";
#define DEFAULT_INFO_DESCRIBER info_describer
#define MK_WSTR_VEC_COURSE_DEFAULT_INFO_DESCRIBER \
	Str_Vec DEFAULT_INFO_DESCRIBER = {COURSE_ID,COURSE_NAME,COURSE_TEACHER,MAX_STUDENTS,COURSE_TYPE}
class Course {
public:
	Course() = default;
//	Course(int32_t course_id, WString course_name, WString course_teacher, int32_t max_students,
//		int32_t current_students, WString course_type);
	Course(Course_default_Info const& info);
	WString show()const;
	int32_t get_current_students()const;
	bool join_student(Student const&stu);
	int32_t check_maxnums()const;
	int32_t check_current_nums()const;
	bool is_join(Student const& stu)const;
	bool student_abandon_course(Student const& stu);
	bool assistant_req(Student& stu);
	bool assitant_here(Assistant const& assi)const;
	bool choose_assistant(Student& stu, Assistant const& assi);
	int32_t get_id()const;
	void set_id(int32_t id);
	bool modify_course_teacher(WString const& teacher);
	bool modify_course_max_student(int32_t max);
	Course_default_Info get_info()const;
	std::vector<Student> get_course_students()const;
	std::vector<Assistant>get_course_assistants()const;
private:
	bool find(Assistant const& key)const;
private:
	Course_default_Info info;
	std::set<Student>current_students;
	std::vector<Assistant*>current_assistants;
};
