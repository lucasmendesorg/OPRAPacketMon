OPRAPacketMon
=============

The OPRA (Options Price Reporting Authority) packet monitor.

Compile and install
-------------------

```
root# make
...
root# make install
```

Run
---

The command line is:

```
OPRAPacketMon [ifnet-IP] [mcast-group-IP] [mcast-port]
```

Try:
```
root# OPRAPacketMon 10.0.1.127 233.43.202.1 11101
```

All logs are sent to syslog being avaliable at [/var/log/]messages file. Use `kill` to send a `SIGUSR1` to OPRAPacketMan and get the latest information about the channels.

```
root# killall -SIGUSR1 OPRAPacketMon && tail -n 48 -f /var/log/messages | grep OPRAPacketMon
```


Take a look into [run.sh](run.sh) for tips.

License
-------

Copyright (c) 2014 [Lucas Mendes](mailto:lucas@lucasmendes.org).

The OPRAPacketMon is licensed under the [GPL v2](LICENSE) license.
