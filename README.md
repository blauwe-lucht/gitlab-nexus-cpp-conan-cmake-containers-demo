# Demo of C++ development process using GitLab, Nexus, Harbour, Conan, CMake and containers

## Usage

```docker compose up -d```

Open project in devcontainer.

## Notes

conan remote add conan-proxy http://172.17.0.1:8081/repository/conan-proxy/ --insecure

gtest requirement doesn't work (anymore) when compiler.cppstd=gnu17. Set it to 17.

## TODO

- Nexus roles are a bit of a mess: anonymous-deploy is probably not needed by the anonymous user, but
is needed by the conan-upload user.
- Add unit tests to fibonacci-webservice.
- Add fibonacci-webservice cmdline flag to list version.
- Add fibonacci-webservice test_package that shows version.
- Add output of fibonacci unit tests to pipeline tests tab.
- Autogenerate version from tag and commits since tag. (how to make this work with the demo repo?)
