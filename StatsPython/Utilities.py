import pprint

def print_results(results: dict, heading: str) -> None:
    """ Print out the results with a heading """
    repeat: int = len(heading)
    separator: str = '-' * repeat
    print(separator)
    print(heading)
    print(separator)
    for result in results:
        k = result
        v = results[k]
        print("{:<12} {:<5.5f}".format(k, v))
    print(separator)


def report_exception(e: Exception) -> None:
    """ Print out details of the exception """
    print(type(e))    # the exception instance
    print(e.args)     # arguments stored in .args
