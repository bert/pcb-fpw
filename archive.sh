#!/bin/sh
git-archive --format=tar --prefix=pcb-fpw/ HEAD | gzip >../../8_archives/pcb-fpw-latest.tar.gz
