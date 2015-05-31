# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

REQUIRED_BOOST_LIBS = ['regex']

def required_boost_libs(conf):
    conf.env.REQUIRED_BOOST_LIBS += REQUIRED_BOOST_LIBS

def configure(conf):
    if not conf.env['LIB_BOOST']:
        conf.report_optional_feature("nnnsim", "nnnsim", False,
                                     "Required boost libraries not found")
        Logs.error ("nnnSIM will not be build as it requires boost libraries of version at least 1.48")
        conf.env['MODULES_NOT_BUILT'].append('nnnsim')
        return
    else:
        present_boost_libs = []
	for boost_lib_name in conf.env['LIB_BOOST']:
	    if boost_lib_name.startswith("boost_"):
	        boost_lib_name = boost_lib_name[6:]
	    
            if boost_lib_name.endswith("-mt"):
	        boost_lib_name = boost_lib_name[:-3]

            present_boost_libs.append(boost_lib_name)

        missing_boost_libs = [lib for lib in REQUIRED_BOOST_LIBS if lib not in present_boost_libs]

	if missing_boost_libs != []:
            conf.report_optional_feature("nnnsim", "nnnsim", False,
                                         "nnnsim requires boost libraries: %s" % ' '.join(missing_boost_libs))
	    conf.env['MODULES_NOT_BUILT'].append('nnnsim')
	    Logs.error ("nnnsim will not be build as it requires boost libraries: %s" % ' '.join(missing_boost_libs))
	    Logs.error ("Please upgrade your distribution or install custom boost libraries")
	    return

	boost_version = conf.env.BOOST_VERSION.split('_')
	if int(boost_version[0]) < 1 or int(boost_version[1]) < 48:
	    conf.report_optional_feature("nnnsim", "nnnsim", False,
			                 "nnnsim requires at least boost version 1.48")
	    conf.env['MODULES_NOT_BUILT'].append('nnnsim')
	    Logs.error ("nnnsim will not be build as it requires boost libraries of version at least 1.48")
	    Logs.error ("Please upgrade your distribution or install custom boost libraries")
	    return	

    conf.env['ENABLE_NNNSIM'] = True
    conf.env['MODULES_BUILT'].append('nnnsim')

    conf.report_optional_feature("nnnsim", "nnnsim", True, "")

def build(bld):
    deps = ['core', 'network', 'point-to-point', 'mobility', 'internet']
    module = bld.create_ns3_module('nnnsim', deps)
    module.module = 'nnnsim'
    module.use += ['BOOST']
    module.source = [
        'helper/nnn-header-helper.cc',
	'helper/nnn-app-helper.cc',
	'helper/nnn-names-container.cc',
	'helper/nnn-names-container-entry.cc',
	'helper/icn-header-helper.cc',
	'helper/nnn-link-control-helper.cc',
	'helper/nnn-face-container.cc',
	'helper/nnn-stack-helper.cc',
	'utils/nnn-limits.cc',
	'utils/nnn-limits-window.cc',
	'utils/nnn-rtt-estimator.cc',
	'utils/nnn-fw-hop-count-tag.cc',
	'utils/tracers/nnn-l3-rate-tracer.cc',
	'utils/tracers/nnn-app-delay-tracer.cc',
	'utils/tracers/nnn-l3-aggregate-tracer.cc',
	'utils/tracers/nnn-l3-tracer.cc',
	'utils/nnn-rtt-mean-deviation.cc',
	'utils/nnn-limits-rate.cc',
	'model/pdus/icn/data/nnn-icn-data.cc',
	'model/pdus/icn/interest/nnn-icn-interest.cc',
	'model/pdus/nnn/inf/nnn-inf.cc',
	'model/pdus/nnn/du/nnn-du.cc',
	'model/pdus/nnn/den/nnn-den.cc',
	'model/pdus/nnn/en/nnn-en.cc',
	'model/pdus/nnn/ren/nnn-ren.cc',
	'model/pdus/nnn/oen/nnn-oen.cc',
	'model/pdus/nnn/do/nnn-do.cc',
	'model/pdus/nnn/nullp/nnn-nullp.cc',
	'model/pdus/nnn/nnn-pdu.cc',
	'model/pdus/nnn/aen/nnn-aen.cc',
	'model/pdus/nnn/so/nnn-so.cc',
	'model/pdus/nnn/nnn-data-pdus.cc',
	'model/pdus/nnn/nnn-en-pdus.cc',
	'model/nnn-face.cc',
	'model/nnn-net-device-face.cc',
	'model/fib/nnn-fib.cc',
	'model/fib/nnn-fib-entry.cc',
	'model/fib/nnn-fib-impl.cc',
	'model/nnpt/nnn-nnpt-entry.cc',
	'model/nnpt/nnn-nnpt.cc',
	'model/nnn-app-face.cc',
	'model/addr-aggr/nnn-addr-aggregator.cc',
	'model/cs/content-store-with-stats.cc',
	'model/cs/content-store-with-probability.cc',
	'model/cs/content-store-with-freshness.cc',
	'model/cs/content-store-nocache.cc',
	'model/cs/content-store-impl.cc',
	'model/cs/nnn-icn-content-store.cc',
	'model/buffers/nnn-pdu-buffer-queue.cc',
	'model/buffers/nnn-pdu-buffer.cc',
	'model/pit/nnn-pit-entry.cc',
	'model/pit/nnn-pit-entry-incoming-face.cc',
	'model/pit/nnn-pit-entry-outgoing-face.cc',
	'model/pit/nnn-pit.cc',
	'model/pit/nnn-pit-impl.cc',
	'model/naming/nnn-icn-exclude.cc',
	'model/naming/nnn-address.cc',
	'model/naming/nnn-icn-name.cc',
	'model/naming/name-component.cc',
	'model/wire/wire-nnnsim.cc',
	'model/wire/nnn-wire.cc',
	'model/wire/wire-nnnsim-icn.cc',
	'model/wire/nnnsim/icn/data/nnnsim-icn-data.cc',
	'model/wire/nnnsim/icn/interest/nnnsim-icn-interest.cc',
	'model/wire/nnnsim/nnn/inf/nnnsim-inf.cc',
	'model/wire/nnnsim/nnn/du/nnnsim-du.cc',
	'model/wire/nnnsim/nnn/den/nnnsim-den.cc',
	'model/wire/nnnsim/nnn/en/nnnsim-en.cc',
	'model/wire/nnnsim/nnn/ren/nnnsim-ren.cc',
	'model/wire/nnnsim/nnn/oen/nnnsim-oen.cc',
	'model/wire/nnnsim/nnn/do/nnnsim-do.cc',
	'model/wire/nnnsim/nnn/nullp/nnnsim-nullp.cc',
	'model/wire/nnnsim/nnn/aen/nnnsim-aen.cc',
	'model/wire/nnnsim/nnn/so/nnnsim-so.cc',
	'model/wire/icn-wire.cc',
	'model/fw/nnn-forwarding-strategy.cc',
	'model/apps/nnn-app.cc',
	'model/apps/nnn-icn-app.cc',
	'model/apps/nnn-icn-producer.cc',
	'model/apps/nnn-icn-consumer.cc',
	'model/apps/nnn-icn-consumer-cbr.cc',
	'model/nnst/nnn-nnst-entry-facemetric.cc',
	'model/nnst/nnn-nnst-entry.cc',
	'model/nnst/nnn-nnst.cc',
	'model/nnn-icn-app-face.cc',
	'model/nnn-l3-protocol.cc',
        ]

    module_test = bld.create_ns3_module_test_library('nnnsim')
    module_test.source = [
        'test/nnnsim-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'nnnsim'
    headers.source = [
	'helper/nnn-app-helper.h',
	'helper/icn-header-helper.h',
	'helper/nnn-stack-helper.h',
	'helper/nnn-names-container.h',
	'helper/nnn-header-helper.h',
	'helper/nnn-names-container-entry.h',
	'helper/nnn-link-control-helper.h',
	'helper/nnn-face-container.h',
	'utils/nnn-limits.h',
	'utils/nnn-rtt-estimator.h',
	'utils/nnn-fw-hop-count-tag.h',
	'utils/tracers/nnn-l3-aggregate-tracer.h',
	'utils/tracers/nnn-l3-rate-tracer.h',
	'utils/tracers/nnn-l3-tracer.h',
	'utils/tracers/nnn-app-delay-tracer.h',
	'utils/nnn-limits-rate.h',
	'utils/nnn-limits-window.h',
	'utils/nnn-rtt-mean-deviation.h',
	'utils/trie/lfu-policy.h',
	'utils/trie/persistent-policy.h',
	'utils/trie/trie-with-policy.h',
	'utils/trie/empty-policy.h',
	'utils/trie/random-policy.h',
	'utils/trie/detail/multi-policy-container.h',
	'utils/trie/detail/functor-hook.h',
	'utils/trie/detail/multi-type-container.h',
	'utils/trie/multi-policy.h',
	'utils/trie/fifo-policy.h',
	'utils/trie/lru-policy.h',
	'utils/trie/counting-policy.h',
	'utils/trie/aggregate-stats-policy.h',
	'utils/trie/trie.h',
	'model/nnn-icn-common.h',
	'model/pdus/icn/data/nnn-icn-data.h',
	'model/pdus/icn/interest/nnn-icn-interest.h',
	'model/pdus/nnn/inf/nnn-inf.h',
	'model/pdus/nnn/du/nnn-du.h',
	'model/pdus/nnn/den/nnn-den.h',
	'model/pdus/nnn/en/nnn-en.h',
	'model/pdus/nnn/ren/nnn-ren.h',
	'model/pdus/nnn/oen/nnn-oen.h',
	'model/pdus/nnn/do/nnn-do.h',
	'model/pdus/nnn/nullp/nnn-nullp.h',
	'model/pdus/nnn/aen/nnn-aen.h',
	'model/pdus/nnn/nnn-en-pdus.h',
	'model/pdus/nnn/so/nnn-so.h',
	'model/pdus/nnn/nnn-pdu.h',
	'model/pdus/nnn/nnn-data-pdus.h',
	'model/nnn-naming.h',
	'model/nnn-net-device-face.h',
	'model/nnn-icn-app-face.h',
	'model/fib/nnn-fib.h',
	'model/fib/nnn-fib-entry.h',
	'model/fib/nnn-fib-impl.h',
	'model/nnpt/nnn-nnpt-entry.h',
	'model/nnpt/nnn-nnpt.h',
	'model/nnn-nnnsim-wire.h',
	'model/nnn-common.h',
	'model/nnn-icn-naming.h',
	'model/addr-aggr/nnn-addr-aggregator.h',
	'model/nnn-icn-pdus.h',
	'model/cs/content-store-nocache.h',
	'model/cs/nnn-icn-content-store.h',
	'model/cs/content-store-with-probability.h',
	'model/cs/content-store-with-freshness.h',
	'model/cs/content-store-impl.h',
	'model/cs/content-store-with-stats.h',
	'model/cs/custom-policies/freshness-policy.h',
	'model/cs/custom-policies/lifetime-stats-policy.h',
	'model/cs/custom-policies/probability-policy.h',
	'model/buffers/nnn-pdu-buffer-queue.h',
	'model/buffers/nnn-pdu-buffer.h',
	'model/pit/nnn-pit.h',
	'model/pit/nnn-pit-entry-impl.h',
	'model/pit/nnn-pit-entry-incoming-face.h',
	'model/pit/nnn-pit-entry.h',
	'model/pit/nnn-pit-entry-outgoing-face.h',
	'model/pit/custom-policies/serialized-size-policy.h',
	'model/pit/nnn-pit-impl.h',
	'model/naming/error.h',
	'model/naming/nnn-icn-name.h',
	'model/naming/nnn-icn-exclude.h',
	'model/naming/blob.h',
	'model/naming/nnn-address.h',
	'model/naming/name-component.h',
	'model/naming/nnn-name-format.h',
	'model/nnn-nnnsim-icn-wire.h',
	'model/wire/wire-nnnsim.h',
	'model/wire/icn-wire.h',
	'model/wire/wire-nnnsim-icn.h',
	'model/wire/nnn-wire.h',
	'model/wire/nnnsim/nnnsim-common-hdr.h',
	'model/wire/nnnsim/icn/data/nnnsim-icn-data.h',
	'model/wire/nnnsim/icn/interest/nnnsim-icn-interest.h',
	'model/wire/nnnsim/nnnsim.h',
	'model/wire/nnnsim/nnnsim-icn.h',
	'model/wire/nnnsim/nnn/inf/nnnsim-inf.h',
	'model/wire/nnnsim/nnn/du/nnnsim-du.h',
	'model/wire/nnnsim/nnn/den/nnnsim-den.h',
	'model/wire/nnnsim/nnn/en/nnnsim-en.h',
	'model/wire/nnnsim/nnn/ren/nnnsim-ren.h',
	'model/wire/nnnsim/nnn/oen/nnnsim-oen.h',
	'model/wire/nnnsim/nnn/do/nnnsim-do.h',
	'model/wire/nnnsim/nnn/nullp/nnnsim-nullp.h',
	'model/wire/nnnsim/nnn/aen/nnnsim-aen.h',
	'model/wire/nnnsim/nnn/so/nnnsim-so.h',
	'model/wire/nnnsim/nnnsim-common.h',
	'model/nnn-pdus.h',
	'model/nnn-l3-protocol.h',
	'model/nnn-app-face.h',
	'model/fw/nnn-forwarding-strategy.h',
	'model/apps/nnn-icn-app.h',
	'model/apps/nnn-icn-consumer-cbr.h',
	'model/apps/nnn-app.h',
	'model/apps/nnn-icn-consumer.h',
	'model/apps/nnn-icn-producer.h',
	'model/nnn-face.h',
	'model/nnst/nnn-nnst.h',
	'model/nnst/nnn-nnst-entry.h',
	'model/nnst/nnn-nnst-entry-facemetric.h',
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

