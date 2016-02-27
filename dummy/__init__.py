try:
	from _dummy import __doc__, make_message, reverse
except ImportError:
	from dummy._dummy import __doc__, make_message, reverse
