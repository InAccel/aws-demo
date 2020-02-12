ifndef AWS_PLATFORM
$(error AWS_PLATFORM is not set)
endif

ifndef XILINX_SDX
$(error XILINX_SDX is not set)
endif

CC = xocc

KERNEL_SOURCES = vadd_kernel.cpp vsub_kernel.cpp
KERNEL_OBJECTS = $(KERNEL_SOURCES:.cpp=.xo)

KERNEL_OPTS = --nk vadd_kernel:2 \
              --sp vadd_kernel_1.m_axi_gmem0:bank0 \
              --sp vadd_kernel_1.m_axi_gmem1:bank0 \
              --sp vadd_kernel_1.m_axi_gmem2:bank0 \
              --sp vadd_kernel_2.m_axi_gmem0:bank1 \
              --sp vadd_kernel_2.m_axi_gmem1:bank1 \
              --sp vadd_kernel_2.m_axi_gmem2:bank1 \
              --nk vsub_kernel:2 \
              --sp vsub_kernel_1.m_axi_gmem0:bank2 \
              --sp vsub_kernel_1.m_axi_gmem1:bank2 \
              --sp vsub_kernel_1.m_axi_gmem2:bank2 \
              --sp vsub_kernel_2.m_axi_gmem0:bank3 \
              --sp vsub_kernel_2.m_axi_gmem1:bank3 \
              --sp vsub_kernel_2.m_axi_gmem2:bank3

all: help

%.xclbin: $(KERNEL_OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(KERNEL_OPTS) --link $(^) --output $(@) --platform $(AWS_PLATFORM) --target hw

%.xo: %.cpp
	$(CC) --compile $(<) --kernel $(*F) --output $(@) --platform $(AWS_PLATFORM) --target hw

help:
	@echo "Build the .xclbin file"
	@echo "make binary/demo.xclbin"
