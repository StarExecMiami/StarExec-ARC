#!/usr/bin/env python3
"""
Selenium script to automate interactions with StarExec web interface.
"""
import argparse
import getpass
import logging
import os
import sys
import time

from selenium import webdriver
from selenium.common.exceptions import TimeoutException, WebDriverException
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.remote.webdriver import WebDriver
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import WebDriverWait

# Constants
DEFAULT_BASE_URL = "https://localhost:8443"
DEFAULT_USERNAME = "admin"
DOWNLOAD_DIR = os.path.expanduser("~/Downloads")
WAIT_TIMEOUT = 60  # seconds
WALLCLOCK_TIMEOUT = 600
CPU_TIMEOUT = WALLCLOCK_TIMEOUT * 2
MAX_MEMORY = 128
CHROME_BINARY = "/bin/google-chrome"  # your chrome path
CHROME_DRIVER = "/usr/local/bin/chromedriver"  # your chromedriver path
# CHROME_BINARY = "/snap/bin/chromium"
# CHROME_DRIVER = "/snap/chromium/current/usr/lib/chromium-browser/chromedriver"
LOG_FILE = "selenium_starexec.log"


def setup_logging() -> logging.Logger:
    """Configure and return a logger for the application."""
    logger = logging.getLogger(__name__)
    logger.setLevel(logging.INFO)

    formatter = logging.Formatter("%(asctime)s - %(levelname)s - %(message)s")

    console_handler = logging.StreamHandler(sys.stdout)
    console_handler.setFormatter(formatter)

    file_handler = logging.FileHandler(LOG_FILE)
    file_handler.setFormatter(formatter)

    logger.addHandler(console_handler)
    logger.addHandler(file_handler)

    return logger


logger = setup_logging()


class StarExecAutomator:
    """Class to automate interactions with the StarExec web interface."""

    def __init__(self, base_url: str, username: str, password: str):
        """
        Initialize the StarExec automator.

        Args:
            base_url: Base URL for StarExec
            username: Login username
            password: Login password
        """
        self.base_url = base_url
        self.username = username
        self.password = password
        self.driver = self._create_driver()

    def _create_driver(self) -> WebDriver:
        """
        Initialize and return a configured Chrome WebDriver.

        Returns:
            Configured Chrome WebDriver instance.

        Raises:
            SystemExit: If driver initialization fails.
        """
        options = Options()
        options.binary_location = CHROME_BINARY
        options.add_argument("--no-sandbox")
        options.add_argument("--disable-dev-shm-usage")
        options.add_argument("--ignore-certificate-errors")
        options.add_argument("--remote-debugging-port=9222")

        try:
            service = Service(CHROME_DRIVER)
            driver = webdriver.Chrome(service=service, options=options)
            driver.implicitly_wait(WAIT_TIMEOUT)
            driver.maximize_window()
            return driver
        except Exception as e:
            logger.error(f"Failed to initialize Chrome WebDriver: {e}")
            raise SystemExit(1)

    def wait_for_element(
        self,
        by: By,
        selector: str,
        timeout: int = WAIT_TIMEOUT,
        condition: callable = EC.element_to_be_clickable,
    ) -> WebDriver:
        """
        Wait for an element to be available on the page.

        Args:
            by: Selenium By selector type
            selector: Element selector string
            timeout: Maximum wait time in seconds
            condition: Expected condition to wait for

        Returns:
            The found web element

        Raises:
            TimeoutException: If element is not found within timeout
        """
        try:
            return WebDriverWait(self.driver, timeout).until(condition((by, selector)))
        except TimeoutException as e:
            logger.error(f"Element not found: {selector} within {timeout} seconds")
            raise e
        except WebDriverException as e:
            logger.error(f"WebDriver exception occurred: {e}")
            raise e
        except Exception as e:
            logger.error(f"Unexpected error occurred: {e}")
            raise e

    def login(self) -> None:
        """
        Log in to StarExec.

        Raises:
            Exception: If login fails
        """
        try:
            self.driver.get(self.base_url)
            logger.info(f"Navigated to URL: {self.driver.current_url}")

            email_field = self.driver.find_element(By.NAME, "j_username")
            password_field = self.driver.find_element(By.NAME, "j_password")
            login_button = self.driver.find_element(By.ID, "loginButton")

            email_field.send_keys(self.username)
            password_field.send_keys(self.password)
            login_button.click()

            # WebDriverWait(self.driver, WAIT_TIMEOUT).until(
            #     EC.url_changes(self.driver.current_url)
            # )
            logger.info(
                f"Logged in successfully, current URL: {self.driver.current_url}"
            )
        except Exception as e:
            logger.error(f"Login failed: {e}")
            raise

    def upload_solver(self, solver_path: str) -> None:
        """
        Upload a solver to StarExec.

        Args:
            solver_path: Path to the solver zip file

        Raises:
            Exception: If upload fails
        """
        try:
            self.driver.get(self.base_url)
            detail_panel = self.wait_for_element(
                By.CSS_SELECTOR,
                "#detailPanel > fieldset:nth-child(6) > legend > span:nth-child(2)",
            )
            detail_panel.click()

            upload_solver_element = self.driver.find_element(
                By.CSS_SELECTOR, "#uploadSolver"
            )
            upload_solver_element.click()

            self.wait_for_element(
                By.CSS_SELECTOR, "#fileLoc", condition=EC.presence_of_element_located
            )
            logger.info("Upload solver element found")
            time.sleep(1)  # Ensure form is fully loaded

            file_input = self.driver.find_element(By.CSS_SELECTOR, "#fileLoc")
            file_input.send_keys(solver_path)

            name_element = self.driver.find_element(By.CSS_SELECTOR, "#name")
            name_element.send_keys("E---3.2.0")

            upload_button = self.driver.find_element(By.CSS_SELECTOR, "#btnUpload")
            upload_button.click()

            logger.info("Solver uploaded successfully")
        except Exception as e:
            logger.error(f"Failed to upload solver: {e}")
            raise

    def upload_benchmark(self, benchmark_path: str) -> None:
        """
        Upload a benchmark to StarExec.

        Args:
            benchmark_path: Path to the benchmark tgz file

        Raises:
            Exception: If upload fails
        """
        try:
            self.driver.get(self.base_url)
            panel_element = self.wait_for_element(
                By.CSS_SELECTOR,
                "#detailPanel > fieldset:nth-child(7) > legend > span:nth-child(2)",
            )
            logger.info("Detail panel is clickable")
            panel_element.click()

            upload_bench_element = self.driver.find_element(
                By.CSS_SELECTOR, "#uploadBench"
            )
            upload_bench_element.click()

            bench_file_input = self.driver.find_element(By.CSS_SELECTOR, "#benchFile")
            bench_file_input.send_keys(benchmark_path)

            bench_upload_button = self.driver.find_element(
                By.CSS_SELECTOR, "#btnUpload"
            )
            bench_upload_button.click()

            logger.info("Benchmark uploaded successfully")
        except Exception as e:
            logger.error(f"Failed to upload benchmark: {e}")
            raise

    def create_job(self) -> None:
        """
        Create a new job in StarExec.

        Raises:
            Exception: If job creation fails
        """
        try:
            self.driver.get(self.base_url)
            panel_element = self.wait_for_element(
                By.CSS_SELECTOR,
                "#detailPanel > fieldset:nth-child(5) > legend > span:nth-child(2)",
            )
            logger.info("Detail panel is clickable")
            panel_element.click()

            add_job_element = self.driver.find_element(By.CSS_SELECTOR, "#addJob")
            add_job_element.click()

            # Configure job parameters
            self._configure_job_parameters()

            next_button = self.driver.find_element(By.CSS_SELECTOR, "#btnNext")
            next_button.click()

            keep_hierarchy_element = self.driver.find_element(
                By.CSS_SELECTOR, "#keepHierarchy"
            )
            keep_hierarchy_element.click()

            done_button = self.driver.find_element(
                By.CSS_SELECTOR, "#btnDone > span.ui-button-text"
            )
            done_button.click()

            logger.info("Job created successfully")
        except Exception as e:
            logger.error(f"Failed to create job: {e}")
            raise

    def _configure_job_parameters(self) -> None:
        """Configure the job parameters with timeouts and memory limits."""
        wallclock_timeout_element = self.driver.find_element(
            By.CSS_SELECTOR, "#wallclockTimeout"
        )
        wallclock_timeout_element.clear()
        wallclock_timeout_element.send_keys(str(WALLCLOCK_TIMEOUT))

        cpu_timeout_element = self.driver.find_element(By.CSS_SELECTOR, "#cpuTimeout")
        cpu_timeout_element.clear()
        cpu_timeout_element.send_keys(str(CPU_TIMEOUT))

        max_memory_element = self.driver.find_element(By.CSS_SELECTOR, "#maxMem")
        max_memory_element.clear()
        max_memory_element.send_keys(str(MAX_MEMORY))

    def run_workflow(self, solver_path: str, benchmark_path: str) -> None:
        """
        Run the full test workflow.

        Args:
            solver_path: Path to the solver file
            benchmark_path: Path to the benchmark file
        """
        try:
            self.login()
            time.sleep(1)
            self.upload_solver(solver_path)
            time.sleep(1)
            self.upload_benchmark(benchmark_path)
            time.sleep(1)
            self.create_job()
            time.sleep(1)

            logger.info("Test workflow completed successfully")
        except Exception as e:
            logger.error(f"Workflow failed: {e}")
            raise

    def cleanup(self) -> None:
        """Close the browser and cleanup resources."""
        if self.driver:
            self.driver.quit()
            logger.info("Browser closed successfully")


def parse_arguments() -> argparse.Namespace:
    """Parse command line arguments."""
    parser = argparse.ArgumentParser(description="StarExec automation script")
    parser.add_argument(
        "--base-url",
        default=DEFAULT_BASE_URL,
        help=f"Base URL for StarExec (default: {DEFAULT_BASE_URL})",
    )
    parser.add_argument(
        "--solver-path", required=True, help="Path to the solver zip file"
    )
    parser.add_argument(
        "--benchmark-path", required=True, help="Path to the benchmark tgz file"
    )
    parser.add_argument(
        "--username",
        default=DEFAULT_USERNAME,
        help=f"Username for StarExec login (default: {DEFAULT_USERNAME})",
    )
    parser.add_argument(
        "--password",
        nargs="?",
        const="",
        help="Password for StarExec login (if not provided, you will be prompted)",
    )
    args = parser.parse_args()

    # Load password from environment variable if not provided via command line
    if (
        args.password is None or args.password == ""
    ) and "STAREXEC_PASSWORD" in os.environ:
        args.password = os.environ["STAREXEC_PASSWORD"]

    return args


def main() -> int:
    """
    Main entry point for the script.

    Returns:
        Exit code (0 for success, 1 for failure)
    """
    args = parse_arguments()

    # Prompt for password if not provided
    if not args.password:
        args.password = getpass.getpass(prompt="Enter your StarExec password: ")

    automator = None
    try:
        automator = StarExecAutomator(args.base_url, args.username, args.password)
        automator.run_workflow(args.solver_path, args.benchmark_path)
        return 0
    except Exception as e:
        logger.error(f"An error occurred during execution: {e}")
        return 1
    finally:
        if automator:
            automator.cleanup()


if __name__ == "__main__":
    sys.exit(main())
