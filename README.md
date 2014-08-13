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

Take a look into [run.sh](run.sh) for tips.

License
-------

Copyright (c) 2014 [Lucas Mendes](mailto:lucas@lucasmendes.org).

The OPRAPacketMon is licensed under the [GPL v2](LICENSE) license.
