#!/bin/sh
git archive --format=tar --prefix=pcb-fpw/ HEAD | gzip >../pcb-fpw-latest.tar.gz
