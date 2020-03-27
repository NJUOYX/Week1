#include "Start.h"

Start::Start():base(base),current_user(nullptr)
{
}


int Start::exc()
{
	return login();
}

int Start::login()
{
	Account_CI ci;
	Account_CI::Account_Info info;
	auto res = ci.top_show(info);
	while (true) {
		switch (res)
		{
		case Account_CI::BaseCall::ROOT_LOGIN_REQUIRE: {
			current_user = new Root_Account(info.id, info.password);
			if (current_user->passit()) {
				ci.responseshow(Account_CI::BaseResponse::ROOT_LOGIN_SUCCESS, info);
				return Root_Operation();
			}
			else
				res = ci.responseshow(Account_CI::BaseResponse::ROOT_LOGIN_FAIL, info);
		}break;
		case Account_CI::BaseCall::STUDENT_LOGIN_REQUIRE: {
			current_user = new Student_Account(info.id, info.password);
			if (current_user->passit()) {
				ci.responseshow(Account_CI::BaseResponse::STUDENT_LOGIN_SUCCESS, info);
				return Stu_Operation();
			}
			else
				res = ci.responseshow(Account_CI::BaseResponse::STUDENT_LOGIN_FAIL, info);
		}break;
		case Account_CI::BaseCall::STUDENT_REGIST_REQUIRE: {
			current_user = new Student_Account(info.id, info.password);
			Student_Account* inst=(Student_Account*)current_user;
			if (inst->regist_it()) {
				ci.responseshow(Account_CI::BaseResponse::STUDENT_REGIST_SUCCESS, info);
				continue;
			}
			else
				res = ci.responseshow(Account_CI::BaseResponse::STUDENT_REGIST_FAIL, info);
		}break;
		case Account_CI::BaseCall::STOP: {
			return -1;
		}break;
		case Account_CI::BaseCall::CONTINUE: {
			continue;
		}break;
		default:
			break;
		}
	}
	return 0;
}

int Start::Root_Operation()
{
	Root_CI ci;
	String info;
	auto res = ci.exc(info);
	while (true) {
		switch (res)
		{
		case Root_CI::Root_Function::LOG_OUT: {
			current_user = nullptr;
			return exc();
		}break;
		case Root_CI::Root_Function::FILE_INFO_IN: {
			if (base == nullptr) {
				String path = ci.get_base_file_path();
				try
				{
					base = new CourseBase(path);
				}
				catch (const std::exception&)
				{
					res = ci.baseresponse(Root_CI::BaseResponse::FILE_INFO_IN_FAIL, info);
					continue;
				}
				return Root_Operation();
			}
			else {
				res = ci.baseresponse(Root_CI::BaseResponse::FILE_INFO_IN_FAIL, Base_had_init);
				continue;
			}
		}break;
		case Root_CI::Root_Function::LIST_ALL_COURSES: {
			if (base == nullptr) {
				res = ci.baseresponse(Root_CI::BaseResponse::LIST_ALL_COURSES_FAIL, Base_not_init);
				continue;
			}
			else {
				auto lists = base->show();
				res = ci.baseresponse(Root_CI::BaseResponse::LIST_ALL_COURSES_SUCCESS,CI::format_wstr_vector(lists));
				return Root_Operation();
			}
		}break;
		case Root_CI::Root_Function::ADD_COURSES: {
			if (base == nullptr) {
				res = ci.baseresponse(Root_CI::BaseResponse::LIST_ALL_COURSES_FAIL, Base_not_init);
				continue;
			}
			else {
				MK_WSTR_VEC_COURSE_DEFAULT_INFO_DESCRIBER;
				WStr_Vec newcourse = ci.get_in(DEFAULT_INFO_DESCRIBER);
				auto course = read_course_from_strs(newcourse);
				auto result = base->add_course(course);
				if (result) {
					res = ci.baseresponse(Root_CI::BaseResponse::ADD_COURSES_SUCCESS, info);
					return Root_Operation();
				}
				else {
					res = ci.baseresponse(Root_CI::BaseResponse::ADD_COURSES_FAIL, info);
					continue;
				}
			}
		}break;
		case Root_CI::Root_Function::DEL_COURSES: {
			if (base == nullptr) {
				res = ci.baseresponse(Root_CI::BaseResponse::LIST_ALL_COURSES_FAIL, Base_not_init);
				continue;
			}
			else {
				WStr_Vec DEFAULT_INFO_DESCRIBER = { COURSE_ID };
				auto s_id = ci.get_in(DEFAULT_INFO_DESCRIBER);
				auto course_id = read_int32_from_strs(s_id);
				auto result = base->del_course(course_id);
				if (result) {
					res = ci.baseresponse(Root_CI::BaseResponse::DEL_COURSES_SUCCESS, info);
					return Root_Operation();
				}
				else {
					res = ci.baseresponse(Root_CI::BaseResponse::DEL_COURSES_FAIL, info);
					continue;
				}
			}
		}break;
		case Root_CI::Root_Function::MODIFY_COURSES: {
			if (base == nullptr) {
				res = ci.baseresponse(Root_CI::BaseResponse::LIST_ALL_COURSES_FAIL, Base_not_init);
				continue;
			}
			else {
				WStr_Vec DEFAULT_INFO_DESCRIBER = { COURSE_ID };
				auto s_id = ci.get_in(DEFAULT_INFO_DESCRIBER);
				auto course_id = read_int32_from_strs(s_id);
				while (true) {
					auto s_choice = ci.get_in({ "选择需要修改的项目：1.教师，2.最大学生数" });
					auto choice = read_int32_from_strs(s_choice);
					if (choice == 1) {
						auto teacher = ci.get_in({ "修改教师为：" });
						auto s_teacher = CI::format_wstr_vector(teacher);
						auto result = base->modify_course_teacher(course_id, s_teacher);
						if (result)
						{
							res = ci.baseresponse(Root_CI::BaseResponse::MODIFY_COURSES_SUCCESS, Teacher_modify_success);
							return Root_Operation();
						}
						else {
							res = ci.baseresponse(Root_CI::BaseResponse::MODIFY_COURSES_FAIL, info);
							continue;
						}
					}
					else if (choice == 2) {
						auto s_num = ci.get_in({ "修改最大学生数为：" });
						auto max_num = read_int32_from_strs(s_num);
						auto result = base->modify_course_max_student(course_id, max_num);
						if (result)
						{
							res = ci.baseresponse(Root_CI::BaseResponse::MODIFY_COURSES_SUCCESS, max_students_modify_success);
							return Root_Operation();
						}
						else {
							res = ci.baseresponse(Root_CI::BaseResponse::MODIFY_COURSES_FAIL, max_students_modify_fail);
							continue;
						}
					}
				}
			}
		}break;
		case Root_CI::Root_Function::CHECK_COURSES: {
			if (base == nullptr) {
				res = ci.baseresponse(Root_CI::BaseResponse::LIST_ALL_COURSES_FAIL, Base_not_init);
				continue;
			}
			else {
				auto s_id = ci.get_in({ COURSE_ID });
				auto id = read_int32_from_strs(s_id);
				auto course = base->get_course(id);
				auto signal = course.show() + "选择具体功能：1.查看选课学生，2.查看选课助教";
				while (true) {
					auto s_choice = ci.get_in({ signal });
					auto choice = read_int32_from_strs(s_choice);
					if (choice == 1) {
						auto stus = course.get_course_students();
						WStr_Vec stuinfo_ls(stus.size());
						for (int i = 0; i < stuinfo_ls.size(); ++i)
							stuinfo_ls[i] = stus[i].get_sid();
						res = ci.baseresponse(Root_CI::BaseResponse::CHECK_COURSES_SUCCESS, CI::format_wstr_vector(stuinfo_ls));
						return Root_Operation();
					}
					else if (choice == 2) {
						auto stus = course.get_course_assistants();
						WStr_Vec assi_info_ls(stus.size());
						for (int i = 0; i < assi_info_ls.size(); ++i)
							assi_info_ls[i] = stus[i].get_sid();
						res = ci.baseresponse(Root_CI::BaseResponse::CHECK_COURSES_SUCCESS,CI::format_wstr_vector(assi_info_ls));
						return Root_Operation();
					}
				}
			}
		}break;
		default:
			break;
		}
	}
	return 0;
}

int Start::Stu_Operation()
{
	Student_CI ci;
	String info;
	auto res = ci.exc(info);
	while (true)
	{
		switch (res)
		{
		case Student_CI::Student_Function::LOG_OUT: {
			current_user = nullptr;
			return exc();
		}
			break;
		case Student_CI::Student_Function::LIST_ALL_COURSES: {
			if (base == nullptr) {
				res = ci.baseresponse(Student_CI::BaseResponse::LIST_ALL_COURSES_FAIL, Base_not_init);
				continue;
			}
			else {
				auto lists = base->show();
				res = ci.baseresponse(Student_CI::BaseResponse::LIST_ALL_COURSES_SUCCESS, CI::format_wstr_vector(lists));
				return Root_Operation();
			}
		}
			break;
		case Student_CI::Student_Function::CHOOSE_COURSE: {

		}
			break;
		case Student_CI::Student_Function::CHECK_MY_COURSES:
			break;
		case Student_CI::Student_Function::GIVE_UP_MY_COURSE:
			break;
		case Student_CI::Student_Function::TO_BE_ASSISTANT:
			break;
		case Student_CI::Student_Function::CHOOSE_MY_ASSISTANT:
			break;
		default:
			break;
		}
	}
	return 0;
}
