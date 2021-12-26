# Help Viewer

A super simple HTML help viewer application that can be easily embedded in another application as a separate executable.

## Build configuration

The following `qmake` variables are available to customize the generated Help Viewer executable :
* `HELP_VIEWER_CONTENT_RESOURCE_FILE` : Set an absolute or a relative path to the `.qrc` file containing the help content (usually simple HTML files). The help content is embedded into the Help Viewer executable to avoid dealing with an external file when the final application is deployed.
* `HELP_VIEWER_PROGRAM_NAME` : Set the name of the help program (i.e. the main window title, not the executable name that will remain always the same). Use double quotes to specify a name that contains the space character, for instance `HELP_VIEWER_PROGRAM_NAME="My program name"`.
