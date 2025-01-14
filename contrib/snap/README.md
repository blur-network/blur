# Snapcraft Build Notes

When calling snapcraft, blur requires much more than the default 2G of memory allocated to container by default, and more cores is helpful too.

None of the `SNAPCRAFT_BUILD_ENVIRONMENT_x` variables are documented, but they exist for specifying cores and memory allocated for build container.

In our case, we need to specify at least 8GB of memory, for a parallel build.

To run snapcraft and have it execute properly, run the following:

```
SNAPCRAFT_BUILD_ENVIRONMENT_MEMORY=16G SNAPCRAFT_BUILD_ENVIRONMENT_CPU=4 snapcraft
```

From root directory of `blur` repository.  Builder may modify `CPU` and `MEMORY` to fit needs.

If it was successful, you should see following when VM/container launches:

```
'SNAPCRAFT_BUILD_ENVIRONMENT_CPU' was set to '4' in the environment. Changing the default allocation upon user request
'SNAPCRAFT_BUILD_ENVIRONMENT_MEMORY' was set to '16G' in the environment. Changing the default allocation upon user request
```

If you do not, `snapcraft clean` and retry
