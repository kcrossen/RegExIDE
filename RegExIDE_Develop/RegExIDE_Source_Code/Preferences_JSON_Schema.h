#ifndef PREFERENCES_JSON_SCHEMA_H
#define PREFERENCES_JSON_SCHEMA_H

QString MyQueryIDE_Preferences_Schema_Text =
R"~~~(
{
  "$schema": "http://json-schema.org/schema#"
  "type": "object",
  "properties": {
    "Preferences": {
      "type": "object",
      "properties": {
        "Home_Directory":
          { "type": "string",
            "description": "Database backups or other data transfers or imports will be found in this directory." },
        "Import_Directory":
          { "type": "string",
            "description": "Database backups or other data transfers or imports will be found in this directory." },
        "Export_Directory":
          { "type": "string",
            "description": "Database and table exports (backups) will be saved to this directory." }
      },
      "required": ["Home_Directory", "Import_Directory", "Export_Directory"]
    },
    "RegEx_Catalog": {
      "type": "array",
      "title": "RegEx_Name",
      "items": {
        "type": "object",
        "properties": {
          "Category":
            { "type": "string",
              "description": "Group RegEx catalog by topic." },
          "RegEx_Name":
            { "type": "string",
              "default": "New RegEx",
              "description": "Name for this RegEx within the category group." },
          "RegEx_Pattern":
            { "type": "string",
              "description": "Regular expression pattern for this transform." },
          "Replace_Pattern":
            { "type": "string",
              "description": "Replace pattern for this transform." },
          "Target":
            { "type": "string",
              "description": "Practice, demonstration, or test for regular expression transform." }
        },
        "required": ["Category", "RegEx_Name", "RegEx_Pattern"]
      }
    }
  }
}
)~~~";

#endif // PREFERENCES_JSON_SCHEMA_H
