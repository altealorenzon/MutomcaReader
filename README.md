# MutomcaReader
Raw Data Reader for the MuTomCa project.

## How to compile
In the directory **MutomcaReader**:

```
cmake <path-to-source>
make
```
Executable can be found in the **MutomcaReader/run/** directory.

## Set the configuration file
Copy the template configuration file **config-example.ini** from the **MutomcaReader/utils/** directory to the **MutomcaReader/run/** directory and rename it **config.ini**. Now you can modify the **config.ini** file in your **MutomcaReader/run/** directory and set all the parameters needed to run the code.

*  Input files:
    | Variable | Type | Description |
    | --- | --- | --- |
    | rawDirName | *string* | path of the input file directory |
    | rawFileNameTubes_1 | *string* | name of the input file for DET 0 (file 1_) |
    | rawFileNamePhi_3 | *string* | name of the input file for  SL 0 (file 3_) |
    | rawFileNameTubes_2  | *string* |  name of the input file for DET 1 (file 2_) |
    | rawFileNamePhi_4	| *string* | name of the input file for  SL 1 (file 4_)
    | maxEventNumber | *int* | maximum number of events to be read |

* Debugging:
    | Variable | Type | Description |
    | --- | --- | --- |
    | debug | *bool* | set to 1 to dump debug messages |


## How to run

After having set the proper configuration options, type:

```
cd run
./goReader
```
