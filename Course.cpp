#include "pch.h"
#include "Course.h"

Course::Course(Course_default_Info const& info):info(info)
{
}

WString Course::show() const
{
	char cstr_id[32] = { 0 };
	_itoa_s(info.course_id, cstr_id,32, 10);
	WString s_id = cstr_id;
	while (s_id.length() < 3)
		s_id = "0" + s_id;
	char cstr_maxnum[32] = { 0 };
	_itoa_s(info.max_students, cstr_maxnum, 32, 10);
	WString s_maxnum = cstr_maxnum;
	//while (s_maxnum.length() < 3)
	//	s_maxnum = "0" + s_maxnum;
	return s_id + " " + info.course_name + " " + 
		info.course_teacher + " " + info.course_type + " " + s_maxnum;
}

int32_t Course::get_current_students() const
{
	return current_students.size();
}

bool Course::join_student(Student const& stu)
{
	if (stu.passit())
		if (info.max_students > current_students.size()) {
			if (current_students.count(stu) != 0)
				return false;
			current_students.insert(stu);
			return true;
		}
	return false;
}

int32_t Course::check_maxnums() const
{
	return info.max_students;
}

int32_t Course::check_current_nums() const
{
	return current_students.size();
}

bool Course::is_join(Student const& stu) const
{
	return current_students.count(stu) !=0;
}

bool Course::student_abandon_course(Student const& stu)
{
	if (current_students.count(stu) == 0)
		return false;
	current_students.erase(stu);
	for(auto i = current_assistants.begin();i!=current_assistants.end();++i)
		if (**i == stu) {
			(**i).dechoice();
			current_assistants.erase(i);
			break;
		}
	return true;
}

bool Course::assistant_req(Student& stu)
{
	if(stu.passit())
		if (current_students.count(stu) != 0) {
			Assistant& key(stu);
			if (!find(key))
			{
				if (!key.choice_full()) {
					current_assistants.push_back(&stu);
					key.addchoice();
					return true;
				}
			}
		}
	return false;
}

bool Course::assitant_here(Assistant const& assi) const
{
	return find(assi);
}

bool Course::choose_assistant(Student& stu, Assistant const& assi)
{
	if (stu.passit()) {
		if (find(assi))
			if (!stu.is_setAssistant()) 
				if (!(stu == assi)) {
					stu.set_myAssistant(assi);
					return true;
				}
			
	}
	return false;
}

int32_t Course::get_id() const
{
	return info.course_id;
}

void Course::set_id(int32_t id)
{
	info.course_id = id;
}

bool Course::modify_course_teacher(WString const& teacher)
{
	info.course_teacher = teacher;
	return true;
}

bool Course::modify_course_max_student(int32_t max)
{
	if(current_students.size()>max)
		return false;
	info.max_students = max;
	return true;
}

Course_default_Info Course::get_info() const
{
	return info;
}

std::vector<Student> Course::get_course_students() const
{
	auto size = current_students.size();
	std::vector<Student>res(size);
	auto i = res.begin();
	auto j = current_students.begin();
	while (i != res.end()) {
		*i++ = *j++;
	}
	return res;
}

std::vector<Assistant> Course::get_course_assistants() const
{
	auto size = current_assistants.size();
	std::vector<Assistant>res(size);
	auto i = res.begin();
	auto j = current_assistants.begin();
	while (i != res.end())
		*i++ = **j++;
	return res;
}



bool Course::find(Assistant const& key) const
{
	for (auto i : current_assistants)
		if (*i == key)
			return true;
	return false;
}




Student::Student(String student_id, String student_password)
	:Assistant(student_id,student_password),is_set_Assistant(false),
	myAssistant()
{
}

Assistant Student::my_assistant() const
{
	return myAssistant;
}

bool Student::set_myAssistant(Assistant const& assi)
{
	if (is_setAssistant())
		return false;
	myAssistant = assi;
	set_I_haveAssistant();
	return true;
}

bool Student::is_setAssistant() const
{
	return is_set_Assistant;
}

void Student::set_I_haveAssistant()
{
	is_set_Assistant = true;
}

bool Assistant::operator==(Assistant const& assi)const
{
	return assi.account_id == this->account_id;
}

bool Assistant::operator<(Assistant const& assi) const
{
	return this->account_id < assi.account_id;
}

Assistant const& Assistant::operator=(Assistant const& assi)
{
	this->account_id = assi.account_id;
	this->account_password = assi.account_password;
	this->current_coursesChoices = assi.current_coursesChoices;
	return assi;
}

bool Assistant::addchoice()
{
	if (current_coursesChoices + 1 > max_coursesChoices)
		return false;
	current_coursesChoices++;
	return true;
}

bool Assistant::dechoice()
{
	if(current_coursesChoices-1<0)
		return false;
	current_coursesChoices--;
	return true;
}

int32_t Assistant::get_max_coursesChoices() const
{
	return max_coursesChoices;
}

String Assistant::get_sid() const
{
	return account_id;
}

Assistant::Assistant():Student_Account(), max_coursesChoices(ASSITANT_MAX_COUESE),
current_coursesChoices(0)
{
}

Assistant::Assistant(String student_id, String student_password) :
	Student_Account(student_id, student_password),max_coursesChoices(ASSITANT_MAX_COUESE),
	current_coursesChoices(0)
{
}

bool Assistant::choice_full() const
{
	return current_coursesChoices>=max_coursesChoices;
}

int32_t Assistant::get_current_coursesChoices() const
{
	return current_coursesChoices;
}

Course_default_Info::Course_default_Info(int32_t course_id, WString course_name, 
	WString course_teacher, int32_t max_students, WString course_type)
	:course_id(course_id),course_name(course_name),course_teacher(course_teacher),
	max_students(max_students),course_type(course_type)
{
}

Course_default_Info::Course_default_Info(WString course_name, WString course_teacher, 
	int32_t max_students, WString course_type)
	: course_id(0), course_name(course_name), course_teacher(course_teacher),
	max_students(max_students), course_type(course_type)
{
}
