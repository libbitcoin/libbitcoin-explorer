These Visual Studio projects have dependencies on various [NuGet packages](https://www.nuget.org/packages).

NuGet packages are downloaded to a local file systems repository. By default the [NuGet Package Manager](http://visualstudiogallery.msdn.microsoft.com/27077b70-9dad-4c64-adcf-c7cf6bc9970c) uses a solution-relative repository path. This can complicate source control and results in multiple repositories across solutions.

A better configuration is to centralize the NuGet repository outside of your `git` directory, for example:

```
-me
    -git
        nuget.config
        -gsl
            -builds
                -msvc
                    +vs2010
                    -vs2012
                        gsl.sln
                        -gsl
                            gsl.vcxproj
                            packages.config
    -nuget
        repositories.config
        +pcre.8.33.0.1
        +pcre.redist.8.33.0.1
        +pcre.symbols.8.33.0.1
```

If properly configured the NuGet Package Manager will share this NuGet repository across all solutions within the `git` directory. There are three steps required in this configuration:

* Create a `nuget` directory as a sibling to your `git` directory.
* Create a `nuget.config` file in the root of your `git` directory.
* Ensure there are no other `nuget.config` files in your `git` directory.

The `nuget.config` should have the [documented structure](http://docs.nuget.org/docs/reference/nuget-config-settings) and should refer to the relative `nuget` directory `..\nuget` as follows:

```
<configuration>
  <config>
    <!-- Allows you to install the NuGet packages in the specified folder,
    instead of the default "$(Solutiondir)\Packages" folder. -->
    <add key="repositoryPath" value="..\nuget" />
  </config>
  <solution>
    <!-- Disable source control integration for the "Packages" folder. -->
    <add key="disableSourceControlIntegration" value="true" />
  </solution>
  <packageRestore>
    <!-- Allow NuGet to download missing packages -->
    <add key="enabled" value="false" />
    <!-- Automatically check for missing packages during build in Visual Studio -->
    <add key="automatic" value="false" />
  </packageRestore>
  <packageSources>
    <!-- Allows you to specify the list of sources to be used while looking for packages. -->
    <add key="NuGet official package source" value="https://nuget.org/api/v2/" />
  </packageSources>
  <disabledPackageSources>
    <!-- "DisabledPackageSources" has the list of sources which are currently disabled. -->
  </disabledPackageSources>
  <activePackageSource>
    <!-- "ActivePackageSource" points to the currently active source. 
    Speciying "(Aggregate source)" as the source value would imply that
    all the current package sources except for the disabled ones are active. -->
    <add key="All" value="(Aggregate source)"  />
  </activePackageSource>
  <packageSourceCredentials>
    <!-- Allows you to set the credentials to access the given package source. -->
    <!-- <feedName>
    <add key="Username" value="foobar" />
    <add key="ClearTextPassword" value="secret" />
    </feedName> -->
  </packageSourceCredentials>
</configuration>
```

With this configuration in place you should experience the following behavior.

When you open one of these Visual Studio projects and then open the Package Manager, you may be informed that there are missing packages. Upon authorizing download of the packages you will see them appear in the `nuget` directory. You will then be able to compile the project(s).
