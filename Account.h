#pragma once
#include"pch.h"
constexpr auto ROOT_ID = "root";
constexpr auto ROOT_PASSWORD = "root";
constexpr auto ACCOUNT_FILE = "G:\\Ñ§µÜ\\Week1pro\\Student_Account_DATA.txt";
constexpr auto FAIL_OPEN_FILE = "Failed to open Student_Account_DATA";
constexpr auto ID_PASSWORD_MAX_LENGTH = 20;
class Root_Account{
public:
	Root_Account() = default;
	Root_Account(String account_id, String account_password);
	virtual bool passit()const;
	bool grammar_check()const;
protected:
	String account_id;
	String account_password;
protected:
	bool string_grammar_check(String const& str)const;
};

class Student_Account :public Root_Account {
public:
	Student_Account() = default;
	Student_Account(String account_id, String account_password);
	bool passit()const override;
	bool regist_it();
};