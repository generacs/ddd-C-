#pragma once
#include <string>
#include <string.h>

using namespace std;

class ConfReader
{
public:
	ConfReader(const string & fileName); 
public:
	~ConfReader(void);

	void setSection(const string &section); 

	string readStr(const string &key) const;
	int readInt(const string &key) const; 

public:
	static int read_profile_string(const char *section, const char *key, char *value,
		int size, const char *file);
	static int read_profile_int(const char *section, const char *key,
		const char *file);

private:
	static int load_ini_file(const char *file, char *buf, int *file_size);
	static int newline(char c);
	static int end_of_string(char c);
	static int left_barce(char c);
	static int right_brace(char c);
	static int parse_file(const char *section, const char *key, const char *buf, int *sec_s, int *sec_e,
		int *key_s, int *key_e, int *value_s, int *value_e);

private:
	string m_fileName;
	string m_section;
};
