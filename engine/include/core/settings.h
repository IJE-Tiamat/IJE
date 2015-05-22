/*
 * Classe que representa um conjunto de configurações.
 *
 * Cada configuração é representada por um par/valor.
 *
 * Autor: Edson Alves
 * Data: 20/05/2015
 * Licença: LGPL. Sem copyright.
 */
#ifndef SETTINGS_H
#define SETTINGS_H

#include "core/exception.h"

#include <sstream>
#include <map>

using std::map;
using std::ostringstream;

class Settings
{
public:
    static Settings * from_file(const string& path) throw (Exception);
    void save(const string& path) throw (Exception);
    
    template<typename T>
    T read(const string& section, const string& name, const T& default_value)
        const;

    template<typename T>
    void write(const string& section, const string& name, const T& value);
    
private:
    map< string, map<string, string> > m_sections;
};

template<typename T> T
Settings::read(const string& section, const string& name,
    const T& default_value) const
{
    auto it = m_sections.find(section);

    if (it != m_sections.end())
    {
        auto jt = it->second.find(name);

        if (jt != it->second.end())
        {
            return jt->second;
        }
    }

    return default_value;
}

template<typename T> void
Settings::write(const string& section, const string& name, const T& value)
{
    ostringstream os;
    os << value;

    auto it = m_sections.find(section);

    if (it == m_sections.end())
    {
        m_sections[section] = map<string, string>();
    }

    m_sections[section][name] = os.str();
}

#endif
