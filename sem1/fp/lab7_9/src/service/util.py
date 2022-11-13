class Utils():
    @staticmethod
    def norm(s: str):
        """
        Returns a string capitalised and stripped, normalising it for comparison 
        *s : str
        """
        return s.upper().strip()
