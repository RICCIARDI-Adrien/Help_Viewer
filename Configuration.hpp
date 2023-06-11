/** @file Configuration.hpp
 * Gather application parametrable settings and translation helpers.
 * @author Adrien RICCIARDI
 */
#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <QLocale>

namespace Configuration
{
    /** Determine and cache system language. */
    void initialize();

    /** Retrieve the current system language Qt identifier.
     * @return The current system language identifier.
     */
    QLocale::Language getSystemLanguageId();

    /** Retrieve the current system language string, like "fr" for French or "en" for English.
     * @return The current system language string.
     */
    QString getSystemLanguageString();
}

#endif // CONFIGURATION_HPP
