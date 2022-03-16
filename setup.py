# -*- encoding: utf-8 -*-
# Source: https://packaging.python.org/guides/distributing-packages-using-setuptools/
# type: ignore
import io
import re

from setuptools import find_packages, setup

dev_requirements = [
    "flake8==3.8.3",
    "flake8==3.8.3",
    "black==22.1.0",
    "pytest==6.2.5",
    "pytest-flake8==1.0.7",
    "pytest-cov==2.8.1",
    "pytest-mypy>=0.8.0",
    "click==8.0.4",
    "picamera==1.13",
]

unit_test_requirements = dev_requirements

integration_test_requirements = dev_requirements

run_requirements = [
    "picamera==1.13",
    "click==8.0.4",
]

with io.open("./camocchi/version.py", encoding="utf8") as version_f:
    version_match = re.search(
        r"^__version__ = ['\"]([^'\"]*)['\"]", version_f.read(), re.M
    )
    if version_match:
        version = version_match.group(1)
    else:
        raise RuntimeError("Unable to find version string.")

with io.open("README.md", encoding="utf8") as readme:
    long_description = readme.read()

setup(
    name="camocchi",
    version=version,
    author="Occhi Project",
    author_email="matheusgoisv@gmail.com",
    packages=find_packages(exclude="tests"),
    include_package_data=True,
    url="https://github.com/PI2-Grupo12/firmware",
    license="COPYRIGHT",
    description="Adicione uma descricao para o seu projeto",
    long_description=long_description,
    zip_safe=False,
    install_requires=run_requirements,
    extras_require={
        "dev": dev_requirements,
        "unit": unit_test_requirements,
        "integration": integration_test_requirements,
    },
    python_requires=">=3.6",
    classifiers=[
        "Intended Audience :: Information Technology",
        "Natural Language :: English",
        "Operating System :: POSIX :: Linux",
        "Programming Language :: Python :: 3.6",
    ],
    keywords=(),
    entry_points={
        "console_scripts": ["camocchi = camocchi.cli:main"],
    },
)
