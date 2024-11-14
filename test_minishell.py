import subprocess
import unittest

class TestMiniShell(unittest.TestCase):
    
    def run_command(self, command):
        """Helper function to run a command in the minishell and return output"""
        try:
            result = subprocess.run(
                ['./minishell'], input=command, text=True, capture_output=True, check=True
            )
            
            lines = result.stdout.strip().split('\n')
            cleaned_output = '\n'.join(lines[1:-1])
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

    def test_pipe(self):
        """Test piping between commands"""
        output = self.run_command('echo Hello | grep Hello\n')
        self.assertEqual(output, "Hello", "Piping failed to work")

    def test_exit(self):
        """Test the exit command"""
        output = self.run_command('exit\n')
        self.assertEqual(output, "", "The exit command did not terminate the shell properly")

    def test_chained_commands(self):
        """Test execution of multiple commands in sequence"""
        output = self.run_command('echo First; echo Second\n')
        self.assertEqual(output, 'First; echo Second', "Chained commands did not execute properly")

    def test_redirection_output(self):
        """Test output redirection to a file"""
        self.run_command('echo Hello > test_output.txt\n')
        with open('test_output.txt', 'r') as f:
            file_content = f.read().strip()
        self.assertEqual(file_content, 'Hello', "Output redirection failed")

    def test_invalid_command(self):
        """Test handling of an invalid command"""
        output = self.run_command('nonexistentcommand\n')
        self.assertTrue('minishell: nonexistentcommand: command not found', "Invalid command handling failed")


if __name__ == '__main__':
    unittest.main() 