# GoogleTestForUnrealEngine
Google Test runner plugin for Unreal Engine

# Installation
To integrate this plugin into your Unreal project, follow these steps:
* Clone this repository into the `<your project>\Plugins\GoogleTestForUE` folder.
* In <your project>.Build.cs file, in the constructor, add the following two lines:

```
PrivateDependencyModuleNames.AddRange(new string[] { "GoogleTestForUE" });

PrivateDefinitions.Add("GTEST_LINKED_AS_SHARED_LIBRARY=1");
```

That's it! You can start writing Google Test tests in your Unreal project.
Happy TDDing!
