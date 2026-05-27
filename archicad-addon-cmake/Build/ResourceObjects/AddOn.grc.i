
'STR#' 32000 "Add-on Name and Description" {
             "Example AddOn"
             "Example AddOn Description..."
}
'STR#' 32001 "Strings for the Menu" {
             "Example AddOn Command... ^E3 ^ES ^EE ^EI ^ED ^ET ^10001"
}
'GDLG' 32002 Modal | grow 40 40 345 220 "" {
              Button 220 187 90 23 LargePlain "OK"
              Button 320 187 90 23 LargePlain "Cancel"
              SingleSelList 10 10 100 165 LargePlain PartialItems 21 HasHeader 21
              TextEdit 205 10 80 20 LargePlain noFrame 255
}
