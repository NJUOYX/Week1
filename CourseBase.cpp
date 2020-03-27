#include "pch.h"
#include "CourseBase.h"

CourseBase::CourseBase():file_path(BASE_FILE)
{
	init_maps();
}

CourseBase::CourseBase(String const& file):file_path(file)
{
	init_maps();
}

WStr_Vec CourseBase::show() const
{
	WStr_Vec res;
	for (auto i : courses)
		res.push_back(i.second.show());
	return res;
}

int32_t CourseBase::get_current_students(int32_t id_index) const
{
	return courses.find(id_index)->second.get_current_students();
}

bool CourseBase::join_student(int32_t id_index, Student const& stu)
{
	if(courses.count(id_index)==0)
		return false;
	auto target = courses.find(id_index);
	return target->second.join_student(stu);
}

int32_t CourseBase::check_maxnums(int32_t id_index) const
{
	auto target = courses.find(id_index);
	return target->second.check_maxnums();
}

int32_t CourseBase::check_current_nums(int32_t id_index) const
{
	auto target = courses.find(id_index);
	return target->second.check_current_nums();
}

int32_t CourseBase::get_course_size() const
{
	return courses.size();
}

Int32_Vec CourseBase::check_student_courses(Student const& stu) const
{
	Int32_Vec res;
	for (auto i : courses) {
		if (i.second.is_join(stu))
			res.push_back(i.first);
	}
	std::sort(res.begin(), res.end());
	return res;
}

bool CourseBase::student_abandon_course(int32_t id_index, Student const& stu)
{
	auto target = courses.find(id_index);
	return target->second.student_abandon_course(stu);
}

bool CourseBase::assistant_req(int32_t id_index, Student& stu)
{
	auto target = courses.find(id_index);
	return target->second.assistant_req(stu);
}

bool CourseBase::assitant_here(int32_t id_index, Assistant const & assi) const
{
	auto target = courses.find(id_index);
	return target->second.assitant_here(assi);
}

bool CourseBase::choose_assitant(int32_t id_index, Student& stu, Assistant const& assi)
{
	auto target = courses.find(id_index);
	return target->second.choose_assistant(stu,assi);
}

bool CourseBase::add_course(Course const& course)
{
	int max = 0;
	for (auto i : courses) {
		max = i.first;
	}
	Course newcourse(course);
	newcourse.set_id(max + 1);
	courses[max + 1] = newcourse;
	return true;
}

bool CourseBase::del_course(int32_t id_index)
{
	if (courses.count(id_index) == 0)
		return false;
	if (courses[id_index].get_current_students() != 0)
		return false;
	courses.erase(id_index);
	return true;
}

Course CourseBase::get_course(int32_t id_index)const
{
	if (courses.count(id_index) == 0)
		return Course();
	return courses.find(id_index)->second;
}

bool CourseBase::modify_course_teacher(int32_t id_index, WString const& teacher)
{
	auto target = courses.find(id_index);
	return target->second.modify_course_teacher(teacher);
}

bool CourseBase::modify_course_max_student(int32_t id_index, int32_t max)
{
	auto target = courses.find(id_index);
	return target->second.modify_course_max_student(max);
}

std::vector<Student> CourseBase::get_course_students(int32_t id_index) const
{
	auto target = courses.find(id_index);
	return target->second.get_course_students();
}

std::vector<Assistant> CourseBase::get_course_assistants(int32_t id_index) const
{
	auto target = courses.find(id_index);
	return target->second.get_course_assistants();
}

void CourseBase::init_maps()
{
	WIFStream is(file_path);
	if (!is.is_open())
		throw FAIL_OPEN_FILE;
	while (!is.eof()) {
		Course_default_Info cdf;
		is >> cdf.course_id >> cdf.course_name >> cdf.course_teacher
			>> cdf.course_type >> cdf.max_students;
		if (cdf.course_id == 0)
			break;
		if (courses.count(cdf.course_id) == 0)
			courses[cdf.course_id] = Course(cdf);
		else
			throw ID_CONFLICTION;
	}
}
