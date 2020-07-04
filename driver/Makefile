
all:mmap
mmap:event
	make insmod -C mmap_drv
event:
	make insmod -C event_drv
start:
	$(shell nohup ./VTSLcd &)
test:
	$(shell ./mmap_drv/test )

clean:
	- make clean -C mmap_drv
	- make clean -C mmap_drv