#!/bin/sh
git archive --format=tar --prefix=pcb-fpw/ HEAD | gzip >../pcb-fpw-$(git describe).tar.gz
