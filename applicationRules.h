#ifndef __APPLICATIONRULE_H__
#define __APPLICATIONRULE_H__

#include <QString>

class ApplicationRules {
    
    public:
        ApplicationRules(const bool isRequired = false, const QString defaultValue = "", const bool isIgnored = false);
        const bool isRequired() {return this->m_isRequired;}
        const QString getDefaultValue() {return m_defaultValue;}
        const bool isIgnored() {return this->m_isIgnored;}

    private:
        bool m_isRequired;
        bool m_isIgnored;
        QString m_defaultValue;
};

#endif
