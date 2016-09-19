## -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

def build(bld):

    module = bld.create_ns3_module('nanonetworks', ['network', 'spectrum'])
    module.source = [
        'helper/nano-helper.cc',
        'model/simple-nano-device.cc',
        'model/nanonode-nano-device.cc',
        'model/nanorouter-nano-device.cc',
        'model/nanointerface-nano-device.cc',
        'model/nano-spectrum-phy.cc',
        'model/nano-spectrum-channel.cc',
        'model/nano-mac-queue.cc',
        'model/nano-mac-header.cc',
        'model/nano-l3-header.cc',
        'model/nano-mac-entity.cc',
        'model/nano-routing-entity.cc',
        'model/flooding-nano-routing-entity.cc',
        'model/random-nano-routing-entity.cc',
        'model/backoff-based-nano-mac-entity.cc',
        'model/transparent-nano-mac-entity.cc',
        'model/ts-ook-based-nano-spectrum-phy.cc',
        'model/nano-spectrum-signal-parameters.cc',
        'model/nano-spectrum-value-helper.cc',
        'model/message-process-unit.cc',
        ]
    module_test = bld.create_ns3_module_test_library('p1906')
    module_test.source = [
        ]
    
    headers = bld(features='ns3header')
    headers.module = 'nanonetworks'
    headers.source = [
        'helper/nano-helper.h',
        'model/simple-nano-device.h',
        'model/nanonode-nano-device.h',
        'model/nanorouter-nano-device.h',
        'model/nanointerface-nano-device.h',
        'model/nano-spectrum-phy.h',
        'model/nano-spectrum-channel.h',
        'model/nano-mac-queue.h',
        'model/nano-mac-header.h',
        'model/nano-l3-header.h',
        'model/nano-mac-entity.h',
        'model/nano-routing-entity.h',
        'model/flooding-nano-routing-entity.h',
        'model/random-nano-routing-entity.h',
        'model/backoff-based-nano-mac-entity.h',
        'model/transparent-nano-mac-entity.h',
        'model/ts-ook-based-nano-spectrum-phy.h',
        'model/nano-spectrum-signal-parameters.h',
        'model/nano-spectrum-value-helper.h',
        'model/message-process-unit.h',
       ]

    if (bld.env['ENABLE_EXAMPLES']):
      bld.add_subdirs('examples')

    bld.ns3_python_bindings()
