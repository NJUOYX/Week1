#include "CI.h"

Account_CI::BaseCall Account_CI::top_show(Account_Info&info)
{
	system("cls");
	WIFStream is(TOP_CI_filepath);
	while (!is.eof()) {
		WString defaultshow;
		std::getline(is, defaultshow);
		std::cout << defaultshow << std::endl;
	}
	int choice;
	while (true) {
		std::cin >> choice;
		switch (choice)
		{
		case 1: {
			std::cout << STUDENT_LOGIN_ID_REQUIRE;
			std::cin >> info.id;
			std::cout << STUDENT_LOGIN_PASSWORD_REQUIRE;
			std::cin >> info.password;
			return BaseCall::STUDENT_LOGIN_REQUIRE;
		}break;
		case 2: {
			std::cout << STUDENT_REGIST_ID_REQUIRE;
			std::cin >> info.id;
			std::cout << STUDENT_REGIST_PASSWORD_REQUIRE;
			std::cin >> info.password;
			return BaseCall::STUDENT_REGIST_REQUIRE;
		}
		case 3: {
			std::cout << ROOT_LOGIN_ID_REQUIRE;
			std::cin >> info.id;
			std::cout << ROOT_LOGIN_PASSWORD_REQUIRE;
			std::cin >> info.password;
			return BaseCall::ROOT_LOGIN_REQUIRE;
		}
		default:
			break;
		}
	}
	return BaseCall::STOP;
}

Account_CI::BaseCall Account_CI::responseshow(BaseResponse response, Account_Info& info)
{
	switch (response)
	{
	case Account_CI::BaseResponse::ROOT_LOGIN_FAIL: {
		std::cout << ROOT_LOGIN_FAIL;
		std::cout << WAITING_TO_CONTINUE;
		String c;
		std::cin >> c;
		if (c == STOP)
			return BaseCall::STOP;
		else {
			return top_show(info);
		}

	}break;
	case Account_CI::BaseResponse::ROOT_LOGIN_SUCCESS: {
		return BaseCall::CONTINUE;
	}break;
	case Account_CI::BaseResponse::STUDENT_LOGIN_FAIL: {
		std::cout << STUDENT_LOGIN_FAIL;
		std::cout << WAITING_TO_CONTINUE;
		String c;
		std::cin >> c;
		if (c == STOP)
			return BaseCall::STOP;
		else
		{
			return top_show(info);
		}
	}break;
	case Account_CI::BaseResponse::STUDENT_LOGIN_SUCCESS: {
		return BaseCall::CONTINUE;
	}break;
	case Account_CI::BaseResponse::STUDENT_REGIST_FAIL: {
		std::cout << STUDENT_REGIST_FAIL;
		std::cout << WAITING_TO_CONTINUE;
		String c;
		std::cin >> c;
		if (c == STOP)
			return BaseCall::STOP;
		else
		{
			return top_show(info);
		}
	}break;

	case Account_CI::BaseResponse::STUDENT_REGIST_SUCCESS: {
		return BaseCall::CONTINUE;
	}break;
	default:
		break;
	}
	return BaseCall::STOP;
}

String Root_CI::get_base_file_path() const
{
	return Root_CI_File_path;
}
