@set TARGET=%1

@echo "# target: %TARGET%"

@if exist %TARGET%.par type %TARGET%.par
@if exist %TARGET%.p01 type %TARGET%.p01
@if exist %TARGET%.std type %TARGET%.std
@if exist %TARGET%.cor type %TARGET%.cor
@if exist %TARGET%.eva type %TARGET%.eva
@if exist %TARGET%.prf type %TARGET%.prf
