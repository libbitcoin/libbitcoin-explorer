# Given a list of unspent outputs, return the optimal subset to satisfy
# a given amount (and return the change).

class OutputInfo(object):

    def __init__(self, point, value):
        self.point = point
        self.value = value

    def __repr__(self):
        return "OutputInfo(point=%s, value=%i)" % (self.point, self.value)

class SelectOutputsResult:

    def __init__(self):
        self._points = []
        self.change = 0

    def add_point(self, point):
        self._points.append(point)

    @property
    def points(self):
        return self._points

    def __repr__(self):
        return "SelectOutputsResult(points=%s, change=%i)" % (
            self._points, self.change)

def min_nonthrow(values, key):
    assert values
    if len(values) == 1:
        return values[0]
    return min(greaters, key=ascend_compare)

def select_outputs(unspent, min_value):
    if not unspent:
        return None
    greaters = [output for output in unspent if not output.value < min_value]
    if greaters:
        ascend_compare = lambda info_a, info_b: \
            info_a.value < info_b.value
        min_greater = min_nonthrow(greaters, key=ascend_compare)
        # Return result with single outpoint
        result = SelectOutputsResult()
        result.add_point(min_greater)
        result.change = min_greater.value - min_value
        return result
    # Not found in greaters. Try several lessers instead.
    # Rearrange them from biggest to smallest. We want to use the least
    # amount of inputs as possible.
    lessers = [output for output in unspent if output.value < min_value]
    # Descending sort
    lessers.sort(key=lambda output: output.value, reverse=True)
    accum = 0
    result = SelectOutputsResult()
    for output in lessers:
        result.add_point(output)
        accum += output.value
        if accum >= min_value:
            result.change = accum - min_value
            return result
    return None

