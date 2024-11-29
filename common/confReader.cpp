#include "confReader.h"

#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>


#define MAX_INI_FILE_SIZE 1024*10

ConfReader::ConfReader(const string& fileName)
{
	m_fileName = fileName;
}

ConfReader::~ConfReader(void)
{
}

void ConfReader::setSection(const string &section)
{
	m_section = section;
}

string ConfReader::readStr(const string &key) const
{
	char buf[1024];
	read_profile_string(m_section.c_str(), key.c_str(), buf, sizeof(buf), m_fileName.c_str());
	for (int i = 0; i<1024; i++)
	{
		if (buf[i] == '\t' || buf[i] == ' ')
			buf[i] = '\0';

		if (buf[i] == '\0')
			break;
	}
	return buf;
}

int ConfReader::readInt(const string &key) const
{
	return read_profile_int(m_section.c_str(), key.c_str(), m_fileName.c_str());
}

int ConfReader::load_ini_file(const char *file, char *buf, int *file_size)
{
	FILE *in = NULL;
	int i = 0;
	*file_size = 0;

	assert(file != NULL);
	assert(buf != NULL);

	in = fopen(file, "r");
	if (NULL == in) {
		return 0;
	}
	buf[i] = fgetc(in);

	while (buf[i] != (char)EOF) {
		i++;
		assert(i < MAX_INI_FILE_SIZE); 
		buf[i] = fgetc(in);
	}

	buf[i] = '\0';
	*file_size = i;

	fclose(in);
	return 1;
}


int ConfReader::read_profile_string(const char *section, const char *key, char *value,
	int size, const char *file)
{
	char buf[MAX_INI_FILE_SIZE] = { 0 };
	int file_size;
	int sec_s, sec_e, key_s, key_e, value_s, value_e;

	assert(section != NULL && strlen(section));
	assert(key != NULL && strlen(key));
	assert(value != NULL);
	assert(size > 0);
	assert(file != NULL &&strlen(key));

	if (!load_ini_file(file, buf, &file_size))
	{
		return 0;
	}
	if (!parse_file(section, key, buf, &sec_s, &sec_e, &key_s, &key_e, &value_s, &value_e))
	{
		return 0; //not find the key
	}
	else
	{
		int cpcount = value_e - value_s;

		if (size - 1 < cpcount)
		{
			cpcount = size - 1;
		}

		//memset(value, 0, size);
		memcpy(value, buf + value_s, cpcount);
		value[cpcount] = '\0';

		return 1;
	}
}

int ConfReader::read_profile_int(const char *section, const char *key,
	const char *file)
{
	char value[32] = { 0 };
	if (!read_profile_string(section, key, value, sizeof(value), file))
	{
		return -1;
	}
	else
	{
		return atoi(value);
	}
}

int ConfReader::newline(char c)
{
	return ('\n' == c || '\r' == c) ? 1 : 0;
}
int ConfReader::end_of_string(char c)
{
	return '\0' == c ? 1 : 0;
}
int ConfReader::left_barce(char c)
{
	return '[' == c ? 1 : 0;
}
int ConfReader::right_brace(char c)
{
	return ']' == c ? 1 : 0;
}
int ConfReader::parse_file(const char *section, const char *key, const char *buf, int *sec_s, int *sec_e,
	int *key_s, int *key_e, int *value_s, int *value_e)
{
	const char *p = buf;
	int i = 0;

	assert(buf != NULL);
	assert(section != NULL && strlen(section));
	assert(key != NULL && strlen(key));

	*sec_e = *sec_s = *key_e = *key_s = *value_s = *value_e = -1;

	while (!end_of_string(p[i])) 
	{
		//find the section
		if ((0 == i || newline(p[i - 1])) && left_barce(p[i]))
		{
			int section_start = i + 1;

			//find the ']'
			do 
			{
				i++;
			} while (!right_brace(p[i]) && !end_of_string(p[i]));


			if (0 == strncasecmp(p+section_start,section, i-section_start)) 
			{
				int newline_start = 0;

				i++;

				//over space char after ']'
				while (isspace(p[i])) 
				{
					i++;
				}
				//find the section
				*sec_s = section_start;
				*sec_e = i;

				while (!(newline(p[i - 1]) && left_barce(p[i])) && !end_of_string(p[i])) 
				{
					int j = 0;
					//get a new line
					newline_start = i;

					while (!newline(p[i]) && !end_of_string(p[i])) 
					{
						i++;
					}
					j = newline_start;
					int valid = j;

					if ('#' != p[j])
					{
						while (j < i && p[j] != '=') 
						{
							j++;

							if (' ' != p[j] && '\t' != p[j] && '=' != p[j])
								valid = j;
							if ('=' == p[j]) 
							{
								if(strncasecmp(key,p+newline_start,valid-newline_start+1)==0)
								{
									*key_s = newline_start;
									*key_e = j - 1;

									valid = j + 1;
									while (' ' == p[valid] || '\t' == p[valid])
										valid++;
									*value_s = valid;
									*value_e = i;

									return 1;
								}
							}
						}
					}

					i++;
				}
			}
		}
		else
		{
			i++;
		}
	}
	return 0;
}