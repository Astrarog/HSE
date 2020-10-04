# NS3 DCE Laboratory using Vagrant Environment
The ojective of this laboratory is to launch NS3 network simulator with DCE support and to research dependency
between TCP window size and TCP transfer speed.

#### 1.  Setup Vagrant
Download from https://www.vagrantup.com/downloads.html and install
#### 2.  Clone current directory

We will suppose that it is cloned into ```<lab_dir>```

#### 3. Setup environment
```
cd <lab_dir>
vagrant up
```
#### 4. Connect to VM and launch perfomance scrtipt
```
vagrant ssh
$run-perf.sh
$exit
```

```run-perf.sh``` is a scrtipt that measure perfomance for all TCP window size values from ___ to ___  (step ___)
and all link delay values from ___ to ___ (step ___). Than it saves all data in file ```~/share/data.csv```.
```~/share``` is a shared folder conntected to ```<lab_dir>```.

#### 5. Destroy VM
```vagrant destroy```

#### 6. Make graphics and Interpret the results
