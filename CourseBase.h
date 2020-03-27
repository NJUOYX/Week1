#pragma once
#include"Course.h"
constexpr auto BASE_FILE = "G:\\Ñ§µÜ\\Week1pro\\Course_Data.txt";
constexpr auto ID_CONFLICTION = "repeated id";

class CourseBase {
public:
	CourseBase();
	CourseBase(String const& file);
	WStr_Vec show()const;
	int32_t get_current_students(int32_t id_index)const;
	bool join_student(int32_t id_index, Student const& stu);
	int32_t check_maxnums(int32_t id_index)const;
	int32_t check_current_nums(int32_t id_index)const;
	int32_t get_course_size()const;
	Int32_Vec check_student_courses(Student const& stu)const;
	bool student_abandon_course(int32_t id_index, Student const& stu);
	bool assistant_req(int32_t id_index, Student& stu);
	bool assitant_here(int32_t id_index, Assistant const & assi)const;
	bool choose_assitant(int32_t id_index, Student& stu, Assistant const& assi);
	bool add_course(Course const& course);
	bool del_course(int32_t id_index);
	Course get_course(int32_t id_index)const;
	bool modify_course_teacher(int32_t id_index, WString const& teacher);
	bool modify_course_max_student(int32_t id_index, int32_t max);
	std::vector<Student> get_course_students(int32_t id_index)const;
	std::vector<Assistant>get_course_assistants(int32_t id_index)const;
private:
	void init_maps();
private:
	std::map<int32_t,Course>courses;//id->course
	String file_path;
};