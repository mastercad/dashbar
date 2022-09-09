#include "applicationRules.h"

#include <QString>

ApplicationRules::ApplicationRules(const bool isRequired /*= false*/, const QString defaultValue /*= ""*/, const bool isIgnored):              m_isRequired(isRequired), m_isIgnored(isIgnored), m_defaultValue(defaultValue) {
}
