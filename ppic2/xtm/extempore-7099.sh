#!/bin/bash

extempore --port 7099 --eval "(bind-val REMOTE_PORT i32 9000) (sys:load \"ppic2/xtm/ppic2-run-remote.xtm\")"
