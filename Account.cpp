#include "pch.h"
#include "Account.h"

Root_Account::Root_Account(String account_id, String account_password):account_id(account_id),
	account_password(account_password)
{
}

bool Root_Account::passit() const
{
	if (account_id == ROOT_ID)
		if (account_password == ROOT_PASSWORD)
			return true;
	return false;
}

bool Root_Account::grammar_check() const
{
	return string_grammar_check(account_id)&&string_grammar_check(account_password);
}

bool Root_Account::string_grammar_check(String const& str) const
{	
	if(str.length()>ID_PASSWORD_MAX_LENGTH)
		return false;
	for (auto i : str) {
		if (isdigit(i))
			continue;
		if (isalpha(i))
			if (!isupper(i))
				continue;
		return false;
	}
	return true;
}

Student_Account::Student_Account(String account_id, String account_password):Root_Account(account_id,account_password)
{
}

bool Student_Account::passit() const
{
	IFStream is(ACCOUNT_FILE);
	if (!is.is_open())
		throw FAIL_OPEN_FILE;
	while (!is.eof()) {
		String id, password;
		is >> id >> password;
		if (account_id == id && account_password == password) {
			is.close();
			return true;
		}
	}
	return false;
}

bool Student_Account::regist_it()
{
	IFStream is(ACCOUNT_FILE);
	if (!is.is_open())
		throw FAIL_OPEN_FILE;
	while (!is.eof()) {
		String id, password;
		is >> id >> password;
		if (id == account_id && password == account_password) {
			is.close();
			return false;
		}
	}
	is.close();
	OFStream os(ACCOUNT_FILE,OFStream::app);
	if (!os.is_open())
		throw FAIL_OPEN_FILE;
	os << account_id << std::endl << account_password<<std::endl;
	os.close();
	return true;
}
