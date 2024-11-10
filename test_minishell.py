import subprocess
import unittest

class TestMiniShell(unittest.TestCase):
    
    def run_command(self, command):
        """Helper function to run a command in the minishell and return output"""
        try:
            result = subprocess.run(
                ['./minishell'], input=command, text=True, capture_output=True, check=True
            )
            # Split the output by newline and remove prompts and the 'exit' line
            lines = result.stdout.strip().split('\n')
            cleaned_output = '\n'.join(lines[1:-1])  # Skip the first (prompt) and last (exit)
            return cleaned_output
        except subprocess.CalledProcessError as e:
            return e.output.strip()

    def test_echo(self):
        """Test that the echo command works as expected"""
        output = self.run_command('echo Hello, World!\n')
        self.assertEqual(output, 'Hello, World!', "The echo command failed")

    def test_pwd(self):
        """Test that the pwd command returns the current directory"""
        output = self.run_command('pwd\n')
        expected_output = subprocess.run(['pwd'], capture_output=True, text=True).stdout.strip()
        self.assertEqual(output, expected_output, "The pwd command failed")

    def test_ls(self):
        """Test that the ls command lists the files correctly"""
        output = self.run_command('ls\n')
        expected_output = subprocess.run(['ls'], capture_output=True, text=True).stdout.strip()
        self.assertEqual(output, expected_output, "The ls command failed")

if __name__ == '__main__':
    unittest.main() 