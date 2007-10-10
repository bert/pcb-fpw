#!/bin/sh
git-archive --format=tar --prefix= HEAD | gzip >../../8_archives/pcb-fpw-latest.tar.gz
