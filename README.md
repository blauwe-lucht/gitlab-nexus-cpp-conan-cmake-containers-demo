# Demo of C++ development process using GitLab, Nexus, Harbour, Conan, CMake and containers

## Prerequisites

You need to have some entries in your hosts file to make everything work correctly:

```hosts
127.0.0.1               gitlab.local
127.0.0.1               nexus.local
127.0.0.1               registry.local
```

You should not have anything listening on ports 8080, 8081, 8083 and port 5000.

## Usage

- ```docker compose up -d```
- Wait until the gitlab container is healthy.
- ```./setup.sh```
- Open the project in vscode in a devcontainer.
- Make changes to sources in _gitlab_push and push them.
- Watch the effect in GitLab: http://gitlab.local:8080, user ```root```, password ```Abcd1234!```
- The library will end up in Nexus: http://nexus.local:8081, user ```admin```, password ```Abcd1234!```
- The container image will end up in the Docker Registry: http://localhost:8083
- After deploying to the test server (TBD) the Swagger UI page of the fibonacci-webservice can
be found at http://<IP of test server>:27372/swagger/ui

## Notes

- During development the gtest requirement suddenly didn't work anymore. It was fixed when I changed the setting ```compiler.cppstd=gnu17``` to ```17``` in ~/.conan2/profiles/default.
- Adding ```"~/.conan2/**"``` to .vscode/settings.json works, but might not be the most stable when
multiple versions of a conan package are installed. Take a look at
[this StackOverflow topic](https://stackoverflow.com/questions/58077908/linking-conan-include-to-vs-code/)
for alternatives.
- Also, you have to ```Developer: Reload Window``` after downloading requirements before IntelliSense will pick them up.
- Using version ranges in requirements is not working yet in Conan repositories in Nexus. So you always have to specify the exact version.

## TODO

- Nexus roles are a bit of a mess: anonymous-deploy is probably not needed by the anonymous user, but
is needed by the conan-upload user.
- Autogenerate version from tag and commits since tag. (how to make this work with the demo repo?)
- Make fibonacci-webservice port configurable through environment.
- Create fibonacci-webUI.
- Add VMs to deploy to.
- Add Ansible scripts to deploy fibonacci-webservice and ficonacci-webUI containers.
- Put Nexus conan-upload user name and password in pipeline secrets.
- setup.sh doesn't work from a clean start, you have to wait a bit and run it again because Nexus isn't ready yet.
- Add devcontainers to fibonacci, fibonacci-webservice and fibonacci-webui so they can be edited like a developer normally would.
- Figure out how to build directly from vscode.
- Figure out how to run unit tests directly from vscode.
