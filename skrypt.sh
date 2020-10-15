#!/bin/bash

LC_ALL=C

if [$(date +%u) -gt 5 ]; then
    echo "weekendzik";
else
    echo "dzien roboczy";
    fi
