/** @file Configuration.hpp
 * Gather application parametrable settings and translation helpers.
 * @author Adrien RICCIARDI
 */
#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <QLocale>

/** The copyright year to embed in the application. */
#define CONFIGURATION_APPLICATION_COPYRIGHT_YEAR "2022"

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
