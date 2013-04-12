IF NOT EXIST utilities\mingw\bin\gcc.exe (
pushd utilities & make --directory=mingw install & popd
) ELSE (
pushd utilities & make --directory=mingw update & popd
)
