# Demo of C++ development process using GitLab, Nexus, Harbour, Conan, CMake and containers

## Usage

- ```docker compose up -d```
- ```./configure-nexus.sh```
- Open the project in vscode in a devcontainer.
- ```conan profile new default --detect```


## Notes

- During development the gtest requirement suddenly didn't work anymore. It was fixed when I changed the setting ```compiler.cppstd=gnu17``` to ```17``` in ~/.conan2/profiles/default.
- Adding ```"~/.conan2/**"``` to .vscode/settings.json works, but might not be the most stable when
multiple versions of a conan package are installed. Take a look at
[this StackOverflow topic](https://stackoverflow.com/questions/58077908/linking-conan-include-to-vs-code/)
for alternatives.

## TODO

- Create GitLab repos for fibonacci and fibonacci-webservice.
- Create pipeline for fibonacci.
- Create pipeline for fibonacci-webservice.
- Nexus roles are a bit of a mess: anonymous-deploy is probably not needed by the anonymous user, but
is needed by the conan-upload user.
- Add fibonacci-webservice cmdline flag to list version.
- Add fibonacci-webservice test_package that shows version.
- Add output of fibonacci unit tests to pipeline tests tab.
- Autogenerate version from tag and commits since tag. (how to make this work with the demo repo?)
- Make fibonacci-webservice port configurable through environment.
- Add health check to service.
- Add swagger UI to service.
- Create fibonacci-webUI.
